// Copyright Epic Games, Inc. All Rights Reserved.

#include "ROTDCharacter.h"
#include "ROTDProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Util/ShootingUtil.h"
#include "FX/BulletHole.h"
#include "FX/BulletImpactEffect.h"
#include "GameMode/ROTDGameMode.h"
#include "GameFramework/InputSettings.h"


//////////////////////////////////////////////////////////////////////////
// AROTDCharacter

AROTDCharacter::AROTDCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	TurnRateGamepad = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

}

void AROTDCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// 绑定背包事件
	PlayerController = Cast<AROTDPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(PlayerController)
	{
		PlayerController->GetInventoryWeaponChangedDelegate().BindUObject(this, &AROTDCharacter::PickUpWeapons);
		PlayerController->GetInventoryItemChangedDelegate().AddUObject(this, &AROTDCharacter::InventoryItemChanged);
	}
	else
	{
		UE_LOG(LogROTD, Warning, TEXT("AROTDPlayerController return NULL"));
	}
	
	IsReloading = false;
	CanFire = true;
	StopReloading = false;

	// Reload Ammo Delay
	ReloadAmmoLatentInfo.Linkage = 0;
	ReloadAmmoLatentInfo.CallbackTarget = this;
	ReloadAmmoLatentInfo.ExecutionFunction = "ReloadAmmoDelay";
	ReloadAmmoLatentInfo.UUID = __LINE__;

	// Fire Delay
	GunFireLatentInfo.Linkage = 0;
	GunFireLatentInfo.CallbackTarget = this;
	GunFireLatentInfo.ExecutionFunction = "GunFireDelay";
	GunFireLatentInfo.UUID = __LINE__;

	// Treatment Delay
	TreatmentLatentInfo.Linkage = 0;
	TreatmentLatentInfo.CallbackTarget = this;
	TreatmentLatentInfo.ExecutionFunction = "TreatmentDelay";
	TreatmentLatentInfo.UUID = __LINE__;

	//Blueprint
	BulletDecalClass = LoadClass<ABulletHole>(nullptr, TEXT("Class'/Script/ROTD.BulletHole'"));
	BulletImpactClass = LoadClass<ABulletImpactEffect>(nullptr, TEXT("Class'/Script/ROTD.BulletImpactEffect'"));

	// 出生时，没有武器
	WeaponType = 0;
	GunID = ESubWeapon::EW_Empty;

	IsAiming = false;
	hud = Cast<AShootingHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
}

//////////////////////////////////////////////////////////////////////////// Input

void AROTDCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AROTDCharacter::OnPrimaryAction);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AROTDCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AROTDCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Mouse" versions handle devices that provide an absolute delta, such as a mouse.
	// "Gamepad" versions are for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AROTDCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AROTDCharacter::LookUpAtRate);
}

void AROTDCharacter::OnPrimaryAction()
{
	// Trigger the OnItemUsed Event
	OnUseItem.Broadcast();
}

void AROTDCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnPrimaryAction();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AROTDCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

void AROTDCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AROTDCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AROTDCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AROTDCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

bool AROTDCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AROTDCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AROTDCharacter::EndTouch);

		return true;
	}
	
	return false;
}

void AROTDCharacter::PickUpWeapons(bool IsAdded, UROTDItems* Item)
{
	if(!IsAdded)
	{
		return;
	}

	if (IsReloading)
	{
		return;
	}

	UWorld* const World = GetWorld();
	FVector Localtion = FVector(0.f, 0.f, 0.f);
	FRotator Rotator = FRotator(0.f);

	UROTDWeaponItem* WeaponItem = (UROTDWeaponItem*)Item;
	if (!WeaponItem) return;

	// Spawn weapon
	AWeaponPickup *PickupWeapon = World->SpawnActor<AWeaponPickup>(WeaponItem->WeaponActor, Localtion, Rotator);
	
	if(!PickupWeapon)
	{
		UE_LOG(LogROTD, Warning, TEXT("Invalid weapon!"));
		return;
	}
	
	// 检查背包中是否已经有子弹
	int Count = PlayerController->GetInventoryItemCount(PickupWeapon->Ammo);
	if(Count > 0)
	{
		PickupWeapon->MaxAmmoCount = Count - PickupWeapon->MagazineBullets;
	}
	
	if (Item->ItemType == EItemType::EItem_Rifle)
	{
		PrimaryWeapon = PickupWeapon;
	}
	else if (Item->ItemType == EItemType::EItem_Pisto)
	{
		SecondWeapon = PickupWeapon;
	}
	else if (Item->ItemType == EItemType::EItem_Knife)
	{
		FourthWeapon = PickupWeapon;
	}
	else if (Item->ItemType == EItemType::EItem_Snipe)
	{
		ThridWeapon = PickupWeapon;
	}

	// 装备捡起的武器
	this->EquipWeapon(PickupWeapon);
}


void AROTDCharacter::InventoryItemChanged(bool IsAdded, UROTDItems* Item)
{
	if(!Item) return;

	if(IsAdded)
	{
		if (Item->ItemType == EItemType::EItem_RifleAmmoSupply)
		{
			if (PrimaryWeapon)
			{
				int Count = PlayerController->GetInventoryItemCount(Item);
				PrimaryWeapon->MaxAmmoCount = Count - PrimaryWeapon->MagazineBullets;
			}
		}
		else if (Item->ItemType == EItemType::EItem_PistoAmmoSupply)
		{
			if (SecondWeapon)
			{
				int Count = PlayerController->GetInventoryItemCount(Item);
				SecondWeapon->MaxAmmoCount = Count - SecondWeapon->MagazineBullets;
			}
		}
		else if (Item->ItemType == EItemType::EItem_ShotgunAmmoSupply)
		{
			if (PrimaryWeapon)
			{
				int Count = PlayerController->GetInventoryItemCount(Item);
				PrimaryWeapon->MaxAmmoCount = Count - PrimaryWeapon->MagazineBullets;
			}
		}
		else if (Item->ItemType == EItemType::EItem_MediaSupply)
		{
			// 刷新药品补给的数量 
			if (!AntiVirusSupply)
			{
				AntiVirusSupply = (UROTDSupplyItem*)Item;
			}
		}
		else if (Item->ItemType == EItemType::EItem_SnifferAmmoSupply)
		{
			if (ThridWeapon)
			{
				int Count = PlayerController->GetInventoryItemCount(Item);
				ThridWeapon->MaxAmmoCount = Count - ThridWeapon->MagazineBullets;
			}
		}

		if (!CurrentWeapon) return;
		// 刷新数据
		hud->UpdateAmmo(CurrentWeapon->MagazineBullets, CurrentWeapon->MaxAmmoCount);
	}
	else
	{
		if (Item->ItemType == EItemType::EItem_RifleAmmoSupply)
		{
			if (PrimaryWeapon)
			{
				int Count = PlayerController->GetInventoryItemCount(Item);
				if(Count > 0)
				{
					if(Count > PrimaryWeapon->MagazineBullets)
					{
						PrimaryWeapon->MaxAmmoCount = Count - PrimaryWeapon->MagazineBullets;
					}
					else
					{
						PrimaryWeapon->MaxAmmoCount = 0;
					}
				}
				else
				{
					PrimaryWeapon->MaxAmmoCount = 0;
					PrimaryWeapon->MagazineBullets = 0;
				}
				
			}
		}
		else if (Item->ItemType == EItemType::EItem_PistoAmmoSupply)
		{
			if (SecondWeapon)
			{
				int Count = PlayerController->GetInventoryItemCount(Item);
				if (Count > 0)
				{
					if (Count > SecondWeapon->MagazineBullets)
					{
						SecondWeapon->MaxAmmoCount = Count - SecondWeapon->MagazineBullets;
					}
					else
					{
						SecondWeapon->MaxAmmoCount = 0;
					}
				}
				else
				{
					SecondWeapon->MaxAmmoCount = 0;
					SecondWeapon->MagazineBullets = 0;
				}
			}
		}
		else if (Item->ItemType == EItemType::EItem_ShotgunAmmoSupply)
		{
			if (PrimaryWeapon)
			{
				int Count = PlayerController->GetInventoryItemCount(Item);
				if (Count > 0)
				{
					if (Count > PrimaryWeapon->MagazineBullets)
					{
						PrimaryWeapon->MaxAmmoCount = Count - PrimaryWeapon->MagazineBullets;
					}
					else
					{
						PrimaryWeapon->MaxAmmoCount = 0;
					}
				}
				else
				{
					PrimaryWeapon->MaxAmmoCount = 0;
					PrimaryWeapon->MagazineBullets = 0;
				}
			}
		}
		else if (Item->ItemType == EItemType::EItem_MediaSupply)
		{
			// 刷新药品补给的数量 
			if (!AntiVirusSupply)
			{
				AntiVirusSupply = (UROTDSupplyItem*)Item;
			}
		}
		else if (Item->ItemType == EItemType::EItem_SnifferAmmoSupply)
		{
			if (ThridWeapon)
			{
				int Count = PlayerController->GetInventoryItemCount(Item);
				ThridWeapon->MaxAmmoCount = Count - ThridWeapon->MagazineBullets;
				if (Count > 0)
				{
					if (Count > ThridWeapon->MagazineBullets)
					{
						ThridWeapon->MaxAmmoCount = Count - ThridWeapon->MagazineBullets;
					}
					else
					{
						ThridWeapon->MaxAmmoCount = 0;
					}
				}
				else
				{
					ThridWeapon->MaxAmmoCount = 0;
					ThridWeapon->MagazineBullets = 0;
				}
			}
		}
	}
	
	if(AntiVirusSupply)
	{
		int Count = PlayerController->GetInventoryItemCount(AntiVirusSupply);
		hud->UpdateMedicalSupply(Count);
	}
}

void AROTDCharacter::Reload()
{
	if(IsReloading)
	{
		return;
	}

	if(!CurrentWeapon) return;

	switch (CurrentWeapon->WeaponType)
	{
	case EWeapon::EW_Hands:
		break;
	case EWeapon::EW_Knife:
		break;
	case EWeapon::EW_Pisto:
	{
		if(CurrentWeapon->MaxAmmoCount == 0)
		{
			return;
		}
		
		if(CurrentWeapon->GunID == ESubWeapon::EW_Magnum)
		{
			IsReloading = true;
			// Play Reload montage
			UAnimMontage* ReloadM = CurrentWeapon->ReloadAnimation;
			if (ReloadM != nullptr)
			{
				CurrentWeapon->FP_Gun->PlayAnimation(ReloadM, false);
			}

			// Load static asset
			FString MagnumReloadMontage = FString(TEXT("AnimMontage'/Game/ROTD/Arms/Animations/ANIM_44_Magnum_Reload_Montage.ANIM_44_Magnum_Reload_Montage'"));
			UAnimMontage* assetMontage = Cast<UAnimMontage>(LoadObject<UAnimMontage>(nullptr, *MagnumReloadMontage));
			if (assetMontage != nullptr)
			{
				// Get the animation object for the arms mesh
				UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
				if (AnimInstance != nullptr)
				{
					AnimInstance->Montage_Play(assetMontage, 1.f);
				}
			}
			
			UKismetSystemLibrary::Delay(this, 5.5f, ReloadAmmoLatentInfo);
		} 
		else if(CurrentWeapon->GunID == ESubWeapon::EW_Glock)
		{

		}

		if((CurrentWeapon->MaxAmmoCount + CurrentWeapon->MagazineBullets) >= CurrentWeapon->MagazineVolum)
		{
			CurrentWeapon->MaxAmmoCount += CurrentWeapon->MagazineBullets;
			CurrentWeapon->MaxAmmoCount -= CurrentWeapon->MagazineVolum;
			CurrentWeapon->MagazineBullets = CurrentWeapon->MagazineVolum;
		}
		else
		{
			CurrentWeapon->MagazineBullets += CurrentWeapon->MaxAmmoCount;
			CurrentWeapon->MaxAmmoCount = 0;
		}
		hud->UpdateAmmo(CurrentWeapon->MagazineBullets, CurrentWeapon->MaxAmmoCount);
		
		break;
	}
	case EWeapon::EW_Rifle:
	{
		if (CurrentWeapon->MaxAmmoCount == 0)
		{
			return;
		}

		if (CurrentWeapon->GunID == ESubWeapon::EW_AK47)
		{
			IsReloading = true;
			// Play Reload montage
			UAnimMontage* ReloadAK = CurrentWeapon->ReloadAnimation;
			if (ReloadAK != nullptr)
			{
				CurrentWeapon->FP_Gun->PlayAnimation(ReloadAK, false);
			}

			// Load static asset
			FString AKReloadMontage = FString(TEXT("AnimMontage'/Game/ROTD/Arms/Animations/ANIM_ArK-47_Reload_Montage.ANIM_ArK-47_Reload_Montage'"));
			UAnimMontage* assetMontage = Cast<UAnimMontage>(LoadObject<UAnimMontage>(nullptr, *AKReloadMontage));
			if (assetMontage != nullptr)
			{
				// Get the animation object for the arms mesh
				UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
				if (AnimInstance != nullptr)
				{
					AnimInstance->Montage_Play(assetMontage, 1.f);
				}
			}

			UKismetSystemLibrary::Delay(this, 3.3f, ReloadAmmoLatentInfo);
		}
		else if(CurrentWeapon->GunID == ESubWeapon::EW_Remington)
		{
			IsReloading = true;
			// 先在蓝图中实现
			CurrentWeapon->WeaponReload();
		}

		if(CurrentWeapon->GunID != ESubWeapon::EW_Remington)
		{
			if ((CurrentWeapon->MaxAmmoCount + CurrentWeapon->MagazineBullets) >= CurrentWeapon->MagazineVolum)
			{
				CurrentWeapon->MaxAmmoCount += CurrentWeapon->MagazineBullets;
				CurrentWeapon->MaxAmmoCount -= CurrentWeapon->MagazineVolum;
				CurrentWeapon->MagazineBullets = CurrentWeapon->MagazineVolum;
			}
			else
			{
				CurrentWeapon->MagazineBullets += CurrentWeapon->MaxAmmoCount;
				CurrentWeapon->MaxAmmoCount = 0;
			}
		}
		
		hud->UpdateAmmo(CurrentWeapon->MagazineBullets, CurrentWeapon->MaxAmmoCount);

		break;
	}
	case EWeapon::EW_Snipe:
	{
		if (CurrentWeapon->MaxAmmoCount == 0)
		{
			return;
		}

		if (CurrentWeapon->GunID == ESubWeapon::EW_STEYRSCOUT)
		{
			IsReloading = true;
			// 先在蓝图中实现
			CurrentWeapon->WeaponReload();
		}
		
		break;
	}
	default:
		break;
	}
}


void AROTDCharacter::OnUpdateShotGunAmmo(int currBullets, int TotalBullets)
{
	hud->UpdateAmmo(currBullets, TotalBullets);
}

void AROTDCharacter::OnFire()
{
	if(!CurrentWeapon)
	{
		return;
	}
		
	if(IsReloading && CurrentWeapon->GunID != ESubWeapon::EW_Remington)
	{
		return;
	}

	if(!CanFire)
	{
		return;
	}

	switch (CurrentWeapon->WeaponType)
	{
	case EWeapon::EW_Hands:
		break;
	case EWeapon::EW_Knife:
	{
		if(CanFire)
		{
			CanFire = false;
			// Play Knife Attack Animation
			if (CurrentWeapon->GunName == "Nipol")
			{
				// Play Arm fire montage
				FString assetPath = FString(TEXT("AnimMontage'/Game/ROTD/Arms/Animations/Anim_Hands_Knife_Attack_03_Montage.Anim_Hands_Knife_Attack_03_Montage'"));
				UAnimMontage* ArmFireMontage = Cast<UAnimMontage>(LoadObject<UAnimMontage>(nullptr, *assetPath));
				if (ArmFireMontage != nullptr)
				{
					// Get the animation object for the arms mesh
					UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
					if (AnimInstance != nullptr)
					{
						AnimInstance->Montage_Play(ArmFireMontage, 1.f);
					}
				}
				UKismetSystemLibrary::Delay(this, 1.6f, GunFireLatentInfo);
			}
		}
		
		break;
	}
	case EWeapon::EW_Pisto:
	{
		if (CurrentWeapon->MagazineBullets < 1)
		{
			if (CurrentWeapon->DryFireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, CurrentWeapon->DryFireSound, GetActorLocation());
			}
			return;
		}

		if (CurrentWeapon->GunName == "Magnum")
		{
			if (CanFire)
			{
				CanFire = false;
				// Muzzle Flash
				this->MuzzleFlash();

				// GunFire
				this->OnGunFire();

				// Play gun fire montage
				UAnimMontage* GunFireMontage = CurrentWeapon->FireAnimation;
				if (GunFireMontage != nullptr)
				{
					CurrentWeapon->FP_Gun->PlayAnimation(GunFireMontage, false);
				}

				// 
				if (IsAiming)
				{
					// Play Arm fire montage
					FString assetPath = FString(TEXT("AnimMontage'/Game/ROTD/Arms/Animations/ANIM_Magnum_ADS_Fire_Montage.ANIM_Magnum_ADS_Fire_Montage'"));
					UAnimMontage* ArmFireMontage = Cast<UAnimMontage>(LoadObject<UAnimMontage>(nullptr, *assetPath));
					if (ArmFireMontage != nullptr)
					{
						// Get the animation object for the arms mesh
						UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
						if (AnimInstance != nullptr)
						{
							AnimInstance->Montage_Play(ArmFireMontage, 1.f);
						}
					}
				}
				else
				{
					// Play Arm fire montage
					FString assetPath = FString(TEXT("AnimMontage'/Game/ROTD/Arms/Animations/ANIM_44_Magnum_Fire_Montage.ANIM_44_Magnum_Fire_Montage'"));
					UAnimMontage* ArmFireMontage = Cast<UAnimMontage>(LoadObject<UAnimMontage>(nullptr, *assetPath));
					if (ArmFireMontage != nullptr)
					{
						// Get the animation object for the arms mesh
						UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
						if (AnimInstance != nullptr)
						{
							AnimInstance->Montage_Play(ArmFireMontage, 1.f);
						}
					}
				}
				UKismetSystemLibrary::Delay(this, 0.5f, GunFireLatentInfo);
			}
		}
		else if (CurrentWeapon->GunName == "Glock")
		{

		}

		break;
	}
	case EWeapon::EW_Rifle:
	{
		if (CurrentWeapon->MagazineBullets < 1)
		{
			if (CurrentWeapon->DryFireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, CurrentWeapon->DryFireSound, GetActorLocation());
			}
			return;
		}

		if (CurrentWeapon->GunID == ESubWeapon::EW_AK47)
		{
			if(CanFire)
			{
				CanFire = false;
				// Muzzle Flash
				this->MuzzleFlash();

				// GunFire
				this->OnGunFire();

				// Play gun fire montage
				UAnimMontage* GunFireMontage = CurrentWeapon->FireAnimation;
				if (GunFireMontage != nullptr)
				{
					CurrentWeapon->FP_Gun->PlayAnimation(GunFireMontage, false);
				}

				if (IsAiming)
				{
					// Play Arm fire montage
					FString assetPath = FString(TEXT("AnimMontage'/Game/ROTD/Arms/Animations/ANIM_ArK-47_ADS-Fire_Montage.ANIM_ArK-47_ADS-Fire_Montage'"));
					UAnimMontage* ArmFireMontage = Cast<UAnimMontage>(LoadObject<UAnimMontage>(nullptr, *assetPath));
					if (ArmFireMontage != nullptr)
					{
						// Get the animation object for the arms mesh
						UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
						if (AnimInstance != nullptr)
						{
							AnimInstance->Montage_Play(ArmFireMontage, 1.f);
						}
					}
				}
				else
				{
					// Play Arm fire montage
					FString assetPath = FString(TEXT("AnimMontage'/Game/ROTD/Arms/Animations/ANIM_ArK-47_Fire_Montage.ANIM_ArK-47_Fire_Montage'"));
					UAnimMontage* ArmFireMontage = Cast<UAnimMontage>(LoadObject<UAnimMontage>(nullptr, *assetPath));
					if (ArmFireMontage != nullptr)
					{
						// Get the animation object for the arms mesh
						UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
						if (AnimInstance != nullptr)
						{
							AnimInstance->Montage_Play(ArmFireMontage, 1.f);
						}
					}
				}
				UKismetSystemLibrary::Delay(this, 0.1f, GunFireLatentInfo);
			}
		}
		else if(CurrentWeapon->GunID == ESubWeapon::EW_Remington)
		{
			if (CanFire)
			{
				CanFire = false;
				// Muzzle Flash
				this->MuzzleFlash();

				// GunFire
				this->OnGunFire();

				// Play gun fire montage
				UAnimMontage* GunFireMontage = CurrentWeapon->FireAnimation;
				if (GunFireMontage != nullptr)
				{
					//CurrentWeapon->FP_Gun->PlayAnimation(GunFireMontage, false);
					UAnimInstance* AnimInstance = CurrentWeapon->FP_Gun->GetAnimInstance();
					if (AnimInstance != nullptr)
					{
						AnimInstance->Montage_Play(GunFireMontage, 1.f);
					}
				}

				if (IsAiming)
				{
					// Play Arm fire montage
					FString assetPath = FString(TEXT("AnimMontage'/Game/ROTD/Arms/Animations/ANiM_870AC_ADSFire_Montage.ANiM_870AC_ADSFire_Montage'"));
					UAnimMontage* ArmFireMontage = Cast<UAnimMontage>(LoadObject<UAnimMontage>(nullptr, *assetPath));
					if (ArmFireMontage != nullptr)
					{
						// Get the animation object for the arms mesh
						UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
						if (AnimInstance != nullptr)
						{
							AnimInstance->Montage_Play(ArmFireMontage, 1.f);
						}
					}
				}
				else
				{
					// Play Arm fire montage
					FString assetPath = FString(TEXT("AnimMontage'/Game/ROTD/Arms/Animations/ANIM_870AC_Fire_Montage.ANIM_870AC_Fire_Montage'"));
					//FString assetPath = FString(TEXT("AnimMontage'/Game/ROTD/Arms/Animations/ANiM_870AC_ADSFire_Montage.ANiM_870AC_ADSFire_Montage'"));
					UAnimMontage* ArmFireMontage = Cast<UAnimMontage>(LoadObject<UAnimMontage>(nullptr, *assetPath));
					if (ArmFireMontage != nullptr)
					{
						// Get the animation object for the arms mesh
						UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
						if (AnimInstance != nullptr)
						{
							AnimInstance->Montage_Play(ArmFireMontage, 1.f);
						}
					}
				}
				UKismetSystemLibrary::Delay(this, 1.3f, GunFireLatentInfo);
			}
		}
		GetWorldTimerManager().SetTimer(AutomaticHandle, this, &AROTDCharacter::OnFire, 0.12f, true);
		break;
	}
	case EWeapon::EW_Snipe:
	{
		if (CurrentWeapon->MagazineBullets < 1)
		{
			if (CurrentWeapon->DryFireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, CurrentWeapon->DryFireSound, GetActorLocation());
			}
			return;
		}

		if (CurrentWeapon->GunID == ESubWeapon::EW_STEYRSCOUT)
		{
			if (CanFire)
			{
				CanFire = false;
				// Muzzle Flash
				this->MuzzleFlash();

				// GunFire
				this->OnGunFire();

				// Play gun fire montage
				UAnimMontage* GunFireMontage = CurrentWeapon->FireAnimation;
				if (GunFireMontage != nullptr)
				{
					CurrentWeapon->FP_Gun->PlayAnimation(GunFireMontage, false);
				}

				if (IsAiming)
				{
					// Play Arm fire montage
					
				}
				else
				{
					
				}

				// Play Arm fire montage
				FString assetPath = FString(TEXT("AnimMontage'/Game/ROTD/Arms/Animations/A_shoot_Montage.A_shoot_Montage'"));
				UAnimMontage* ArmFireMontage = Cast<UAnimMontage>(LoadObject<UAnimMontage>(nullptr, *assetPath));
				if (ArmFireMontage != nullptr)
				{
					// Get the animation object for the arms mesh
					UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
					if (AnimInstance != nullptr)
					{
						AnimInstance->Montage_Play(ArmFireMontage, 1.f);
					}
				}

				UKismetSystemLibrary::Delay(this, 1.5f, GunFireLatentInfo);
			}
		}

		break;
	}
	default:
		break;
	}
}


void AROTDCharacter::OnStopFire()
{
	if (CurrentWeapon == nullptr)
	{
		return;
	}

	if(CurrentWeapon->WeaponType != EWeapon::EW_Rifle)
	{
		return;
	}

	GetWorldTimerManager().ClearTimer(AutomaticHandle);
}

void AROTDCharacter::OnAimDownSight()
{
	if(CurrentWeapon == nullptr)
	{
		return;
	}

	if (CurrentWeapon->WeaponType == EWeapon::EW_Knife || CurrentWeapon->WeaponType == EWeapon::EW_Hands)
	{
		return;
	}

	IsAiming = true;
	hud->SetCrossWidgetVisible(false);

	CurrentWeapon->WeaponADS();
}

void AROTDCharacter::OnRecoverAimDownSight()
{
	if (CurrentWeapon == nullptr)
	{
		return;
	}

	if (CurrentWeapon->WeaponType == EWeapon::EW_Knife || CurrentWeapon->WeaponType == EWeapon::EW_Hands)
	{
		return;
	}

	IsAiming = false;
	hud->SetCrossWidgetVisible(true);

	CurrentWeapon->WeaponRecoverADS();
}

void AROTDCharacter::DropMagazine()
{
	if (CurrentWeapon->ReloadDropSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CurrentWeapon->ReloadDropSound, GetActorLocation());
	}
}

void AROTDCharacter::InsertMagazine()
{
	if (CurrentWeapon->ReloadInsertSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CurrentWeapon->ReloadInsertSound, GetActorLocation());
	}
}


void AROTDCharacter::CloseCylinder()
{
	if (CurrentWeapon->GunName == "Magnum")
	{
		FString CloseSoundPath = FString(TEXT("SoundCue'/Game/ROTD/Sounds/Gun/gun_revolver_pistol_cylinder_close_04_Cue.gun_revolver_pistol_cylinder_close_04_Cue'"));
		USoundBase* CloseSound = Cast<USoundBase>(LoadObject<USoundBase>(nullptr, *CloseSoundPath));
		if (CloseSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CloseSound, GetActorLocation());
		}
	}
}

void AROTDCharacter::ReloadMagazine()
{
	if (CurrentWeapon->ReloadLoadSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CurrentWeapon->ReloadLoadSound, GetActorLocation());
	}
}

void AROTDCharacter::MuzzleFlash()
{
	if (!CurrentWeapon)
	{
		return;
	}

	CurrentWeapon->FP_PointLight->SetIntensity(10000.0f);
	CurrentWeapon->FP_Muzzle->SetActive(true);

	// Delay 0.1
	FLatentActionInfo LatentInfo;
	LatentInfo.Linkage = 0;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = "DelayAndDisplayMuzzle";
	LatentInfo.UUID = __LINE__;
	UKismetSystemLibrary::Delay(this, 0.1f, LatentInfo);
}


void AROTDCharacter::ApplyDamageTo(FHitResult Hit)
{
	float damage = FMath::RandRange(10.f, 25.f);
	AActor* DamagedActor = Hit.GetActor();
	FHitResult HitOut = Hit;
	FVector Direction = Hit.ImpactNormal;
	TSubclassOf<UDamageType> DamageType;
	UGameplayStatics::ApplyPointDamage(DamagedActor, damage, Direction, HitOut, nullptr, this, DamageType);
}

void AROTDCharacter::ShellEjection()
{
	if(CurrentWeapon == NULL)
	{
		return;
	}

	UWorld* const World = GetWorld();
	FVector Localtion = FVector(0.f, 0.f, 0.f);
	FRotator Rotator = FRotator(0.f);

	//ShellEjection
	USkeletalMeshSocket const* mesh = CurrentWeapon->FP_Gun->GetSocketByName("ShellEjection");
}

void AROTDCharacter::DelayAndDisplayMuzzle()
{
	if (!CurrentWeapon)
	{
		return;
	}
	CurrentWeapon->FP_Muzzle->SetActive(false);
	CurrentWeapon->FP_PointLight->SetIntensity(0);
}


void AROTDCharacter::ReloadAmmoDelay()
{
	if (!CurrentWeapon)
	{
		return;
	}

	IsReloading = false;
}


void AROTDCharacter::TreatmentDelay()
{
	
	if (MedicalSupply) {
		MedicalSupply->FP_Supply->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));
	}
	MedicalSupply->Destroy(true);
	MedicalSupply = NULL;

	if (CurrentWeapon) {
		if (CurrentWeapon->WeaponType == EWeapon::EW_Rifle)
		{
			WeaponType = (int)EWeapon::EW_Rifle;
			CurrentWeapon->FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Rifle_AK"));
		}
		else if (CurrentWeapon->WeaponType == EWeapon::EW_Pisto)
		{
			WeaponType = 2;
			CurrentWeapon->FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Pisto_Magnum"));
		}
		else if (CurrentWeapon->WeaponType == EWeapon::EW_Knife)
		{
			WeaponType = (int)EWeapon::EW_Knife;
			CurrentWeapon->FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Palm_R"));
		}
		else if (CurrentWeapon->WeaponType == EWeapon::EW_Snipe)
		{
			WeaponType = (int)EWeapon::EW_Snipe;
		}
	}
}

void AROTDCharacter::GunFireDelay()
{
	if (!CurrentWeapon)
	{
		return;
	}

	CanFire = true;
}

void AROTDCharacter::OnGunFire()
{
	if (CurrentWeapon->FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CurrentWeapon->FireSound, GetActorLocation());
	}

	CurrentWeapon->BulletShellDrop();

	// Camera Shot
	UCameraComponent* FirstCamera = this->FirstPersonCameraComponent;
	FVector TraceStart = FirstCamera->GetComponentLocation();

	if(CurrentWeapon->GunID != ESubWeapon::EW_Remington)
	{
		float BulletSpread = 120.f;
		float calu = BulletSpread * -1;
		float x = FMath::RandRange(calu, BulletSpread);
		float y = FMath::RandRange(calu, BulletSpread);
		float z = FMath::RandRange(calu, BulletSpread);

		FVector TraceEnd = TraceStart + FirstCamera->GetForwardVector() * 20000.f + FVector(x, y, z);

		FHitResult Hit;
		FCollisionQueryParams queryParam;
		queryParam.bReturnPhysicalMaterial = true;
		queryParam.AddIgnoredActor(this);
		bool isHit = GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, queryParam);

		if (isHit)
		{
			EImpactType Type = FShootingUtil::GetInstance()->GetImpactType(Hit.PhysMaterial.Get());

			// Retrieve BulletImpactData from GameMode
			AROTDGameMode* GameMode = Cast<AROTDGameMode>(GetWorld()->GetAuthGameMode());
			bool Success = false;
			FBulletImpact BulletImpact;
			BulletImpact = GameMode->FindBulletImpact(Type, Success);

			if (!Success)
			{
				return;
			}

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				ApplyDamageTo(Hit);
				FRotator Rotator1 = UKismetMathLibrary::MakeRotFromX(Hit.ImpactNormal);
				if (BulletImpact.BulletDecals.Num() != 0)
				{
					int32 index = FMath::RandRange(0, BulletImpact.BulletDecals.Num() - 1);
					if (!BulletImpact.BulletDecals[index])
					{
						return;
					}

					UMaterialInterface* MaterialIns = Cast<UMaterialInterface>(BulletImpact.BulletDecals[index]);
					if (MaterialIns)
					{
						ABulletHole* BulletDecal = World->SpawnActor<ABulletHole>(BulletDecalClass, Hit.Location, Rotator1);
						BulletDecal->SetBulletHoleMaterial(MaterialIns);
					}
				}

				UNiagaraSystem* NiagaraSys = Cast<UNiagaraSystem>(BulletImpact.ImpactNiagara);

				UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, NiagaraSys, Hit.Location, FRotator(0, 0, 0));
			}
		}
	}
	else
	{
		for(int i = 0; i < 6; i++)
		{
			float BulletSpread = 600.f;
			float calu = BulletSpread * -1;
			float x = FMath::RandRange(calu, BulletSpread);
			float y = FMath::RandRange(calu, BulletSpread);
			float z = FMath::RandRange(calu, BulletSpread);

			FVector TraceEnd = TraceStart + FirstCamera->GetForwardVector() * 20000.f + FVector(x, y, z);

			FHitResult Hit;
			FCollisionQueryParams queryParam;
			queryParam.bReturnPhysicalMaterial = true;
			queryParam.AddIgnoredActor(this);
			bool isHit = GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, queryParam);

			if (isHit)
			{
				EImpactType Type = FShootingUtil::GetInstance()->GetImpactType(Hit.PhysMaterial.Get());

				// Retrieve BulletImpactData from GameMode
				AROTDGameMode* GameMode = Cast<AROTDGameMode>(GetWorld()->GetAuthGameMode());
				bool Success = false;
				FBulletImpact BulletImpact;
				BulletImpact = GameMode->FindBulletImpact(Type, Success);

				if (!Success)
				{
					return;
				}

				UWorld* const World = GetWorld();
				if (World != nullptr)
				{
					ApplyDamageTo(Hit);
					FRotator Rotator1 = UKismetMathLibrary::MakeRotFromX(Hit.ImpactNormal);
					if (BulletImpact.BulletDecals.Num() != 0)
					{
						int32 index = FMath::RandRange(0, BulletImpact.BulletDecals.Num() - 1);
						if (!BulletImpact.BulletDecals[index])
						{
							return;
						}

						UMaterialInterface* MaterialIns = Cast<UMaterialInterface>(BulletImpact.BulletDecals[index]);
						if (MaterialIns)
						{
							ABulletHole* BulletDecal = World->SpawnActor<ABulletHole>(BulletDecalClass, Hit.Location, Rotator1);
							BulletDecal->SetBulletHoleMaterial(MaterialIns);
						}
					}

					UNiagaraSystem* NiagaraSys = Cast<UNiagaraSystem>(BulletImpact.ImpactNiagara);

					UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, NiagaraSys, Hit.Location, FRotator(0, 0, 0));
				}
			}
		}
	}
	
	// 更新背包子弹
	PlayerController->RemoveInventoryItem(CurrentWeapon->Ammo, 1);
	hud->UpdateAmmo(--CurrentWeapon->MagazineBullets, CurrentWeapon->MaxAmmoCount);
}

void AROTDCharacter::SwitchWeapons(EWeapon CurrWeaponType)
{
	switch (CurrWeaponType)
	{	// 如果当前是步枪，切换顺序：步枪->手枪->狙击枪->刀->空手
	case EWeapon::EW_Rifle:
		if(SecondWeapon)
		{
			WeaponType = 2;
		}
		else if(ThridWeapon)
		{
			WeaponType = 4;
		}
		else if(FourthWeapon)
		{
			WeaponType = 1;
		}
		else
		{
			WeaponType = 0;
		}
		break;
	case EWeapon::EW_Pisto:
		if(ThridWeapon)
		{
			WeaponType = 4;
		}
		else if(FourthWeapon)
		{
			WeaponType = 1;
		}
		else if (PrimaryWeapon)
		{
			WeaponType = 3;
		}
		else
		{
			WeaponType = 0;
		}
		break;
	case EWeapon::EW_Knife:
		if(PrimaryWeapon)
		{
			WeaponType = 3;
		}
		else if(SecondWeapon)
		{
			WeaponType = 2;
		}
		else if(ThridWeapon)
		{
			WeaponType = 4;
		}
		else
		{
			WeaponType = 0;
		}
		break;
	case EWeapon::EW_Snipe:
		if (FourthWeapon)
		{
			WeaponType = 1;
		}
		else if (PrimaryWeapon)
		{
			WeaponType = 3;
		}
		else if (SecondWeapon)
		{
			WeaponType = 2;
		}
		else
		{
			WeaponType = 0;	
		}
	default:
		break;
	}

	if(WeaponType == 1)
	{
		this->EquipWeapon(FourthWeapon);
	}
	else if(WeaponType == 2)
	{
		this->EquipWeapon(SecondWeapon);
	}
	else if(WeaponType == 3)
	{
		this->EquipWeapon(PrimaryWeapon);
	}
	else if(WeaponType == 4)
	{
		this->EquipWeapon(ThridWeapon);
	}
	else if (WeaponType == 0)
	{
		if (CurrentWeapon) {
			CurrentWeapon->FP_Gun->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));
		}
		CurrentWeapon = NULL;
		GunID = ESubWeapon::EW_Empty;
	}
}

void AROTDCharacter::EquipGunFlashlight(APickUpItemBase* ItemBase)
{
	
}

void AROTDCharacter::TreatSelf(EWeapon CurrWeaponType)
{
	// 背包中是否还有抗生素
	if(!AntiVirusSupply) return;
	int Count = PlayerController->GetInventoryItemCount((UROTDItems *)AntiVirusSupply);
	if(Count <= 0)
	{
		return;
	}

	if(!PlayerController->RemoveInventoryItem(AntiVirusSupply))
	{
		UE_LOG(LogROTD, Warning, TEXT("TreatSelf: no more supply "));
		AntiVirusSupply = NULL;
		return;
	}
	
	int NewCount = PlayerController->GetInventoryItemCount((UROTDItems*)AntiVirusSupply);
	hud->UpdateMedicalSupply(NewCount);

	UWorld* const World = GetWorld();
	FVector Localtion = FVector(0.f, 0.f, 0.f);
	FRotator Rotator = FRotator(0.f);
	UClass* AntivirusClass = LoadClass<ASupplyPickup>(nullptr, TEXT("'/Game/ROTD/Blueprint/Supplys/Antivirus_BP.Antivirus_BP_C'"));
	// Spawn Supply 
	if (MedicalSupply == NULL)
	{
		MedicalSupply = World->SpawnActor<ASupplyPickup>(AntivirusClass, Localtion, Rotator);
	}

	if (!MedicalSupply)
	{
		return;
	}

	if (CurrentWeapon) {
		// Play low down animation
		UAnimMontage* lowMontage = CurrentWeapon->LowAnimation;
		if (lowMontage != nullptr)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(lowMontage, 1.f);
			}
		}
		CurrentWeapon->FP_Gun->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));
	}
	else
	{
		if (WeaponType == 0)
		{
			// Empty hands low down
			FString assetPath = FString(TEXT("AnimMontage'/Game/ROTD/Arms/Animations/Anim_Hands_Empty_Down_Montage.Anim_Hands_Empty_Down_Montage'"));
			UAnimMontage* ArmFireMontage = Cast<UAnimMontage>(LoadObject<UAnimMontage>(nullptr, *assetPath));
			if (ArmFireMontage != nullptr)
			{
				// Get the animation object for the arms mesh
				UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
				if (AnimInstance != nullptr)
				{
					AnimInstance->Montage_Play(ArmFireMontage, 1.f);
				}
			}
		}
	}

	MedicalSupply->FP_Supply->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Supply_Antivirus"));

	// Play inject montage
	UAnimMontage* SyringsMontage = MedicalSupply->UsedAnimation;
	if (SyringsMontage != nullptr)
	{
		MedicalSupply->FP_Supply->PlayAnimation(SyringsMontage, false);
	}

	FString assetPath = FString(TEXT("AnimMontage'/Game/ROTD/Arms/Animations/Anim_Hands_Syringe_03_Using_Montage.Anim_Hands_Syringe_03_Using_Montage'"));
	UAnimMontage* ArmFireMontage = Cast<UAnimMontage>(LoadObject<UAnimMontage>(nullptr, *assetPath));
	if (ArmFireMontage != nullptr)
	{
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(ArmFireMontage, 1.f);
		}
	}

	// Delay
	UKismetSystemLibrary::Delay(this, 2.2f, TreatmentLatentInfo);
}

void AROTDCharacter::EquipWeapon(AWeaponPickup* Weapon)
{
	if(!Weapon)
	{
		UE_LOG(LogROTD, Warning, TEXT("EquipWeapon: weapon is null "));
		return;
	}
	// Spawn weapon
	if (CurrentWeapon) {
		// Play low down animation
		UAnimMontage* lowMontage = CurrentWeapon->LowAnimation;
		if (lowMontage != nullptr)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(lowMontage, 1.f);
			}
		}

		CurrentWeapon->FP_Gun->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));
	}
	
	CurrentWeapon = Weapon;

	if (Weapon->WeaponType ==  EWeapon::EW_Rifle)
	{
		WeaponType = (int)EWeapon::EW_Rifle;
		GunID = Weapon->GunID;
		if(GunID == ESubWeapon::EW_AK47)
		{
			CurrentWeapon->FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Rifle_AK"));
		}
		else if(GunID == ESubWeapon::EW_Remington)
		{
			CurrentWeapon->FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Rifle_Reminton"));
		}
	}
	else if (Weapon->WeaponType == EWeapon::EW_Pisto)
	{
		WeaponType = 2;
		GunID = Weapon->GunID;
		CurrentWeapon->FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Pisto_Magnum"));
		
	}
	else if (Weapon->WeaponType == EWeapon::EW_Knife)
	{
		WeaponType = (int)EWeapon::EW_Knife;
		GunID = Weapon->GunID;
		CurrentWeapon->FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Palm_R"));
	}
	else if (Weapon->WeaponType == EWeapon::EW_Snipe)
	{
		WeaponType = (int)EWeapon::EW_Snipe;
		GunID = Weapon->GunID;
		CurrentWeapon->FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Snipe_SSG08"));
	}
	else
	{
		if (CurrentWeapon) {
			CurrentWeapon->FP_Gun->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));
		}
	}

	// Play raise animation
	UAnimMontage* raiseMontage = CurrentWeapon->RaiseAnimation;
	if (raiseMontage != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(raiseMontage, 1.f);
		}
	}

	// WidgetUI update 
	if (hud == NULL)
	{
		return;
	}

	if (!CurrentWeapon)
	{
		hud->PointWidget->SetVisibility(ESlateVisibility::Visible);
		hud->CrossWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		hud->PointWidget->SetVisibility(ESlateVisibility::Hidden);
		hud->CrossWidget->SetVisibility(ESlateVisibility::Visible);
	}

	// 刷新武器以及子弹
	hud->SwitchWeapon((UROTDWeaponItem*)CurrentWeapon->ItemType);
	hud->UpdateAmmo(CurrentWeapon->MagazineBullets, CurrentWeapon->MaxAmmoCount);
}

void AROTDCharacter::UpdatePlayerHealth(float CurrentHealth, float MaxHealth)
{
	if(hud)
	{
		hud->UpdateHealth(CurrentHealth, MaxHealth);
	}
}

void AROTDCharacter::PlayerDieAndHideCross()
{
	if (hud)
	{
		hud->SetCrossWidgetVisible(false);
	}
}

void AROTDCharacter::DropWeaponAndSwitchWeapon()
{
	// 背包中移除当前武器
	if(PlayerController == NULL) return;

	if(CurrentWeapon == NULL) return;

	bool IsRemove = PlayerController->RemoveInventoryItem(CurrentWeapon->ItemType);
	
	if(!IsRemove)
	{
		UE_LOG(LogROTD, Warning, TEXT("RemoveInventoryItem not success"));
	}

	// 并移除武器缓存
	EWeapon type = CurrentWeapon->WeaponType;
	if(type == EWeapon::EW_Rifle)
	{
		PrimaryWeapon = NULL;
	}
	else if(type == EWeapon::EW_Pisto)
	{
		SecondWeapon = NULL;
	}
	else if(type == EWeapon::EW_Snipe)
	{
		ThridWeapon = NULL;
	}
	else if(type == EWeapon::EW_Knife)
	{
		FourthWeapon = NULL;
	}

	// 切换至下一把
	this->SwitchWeapons(type);
}
