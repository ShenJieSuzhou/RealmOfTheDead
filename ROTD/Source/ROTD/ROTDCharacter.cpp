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
#include "CusActor/BulletHole.h"
#include "CusActor/BulletImpactEffect.h"
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

	// Hands
	EmptyHands = NULL;
	// Knife
	WeaponKnife = NULL;
	// Pisto 
	WeaponPisto = NULL;
	// Rifle
	WeaponRifle = NULL;
	// Snipe
	WeaponSnipe = NULL;

	IsReloading = false;
	CanFire = true;

	// Reload Ammo Delay
	ReloadAmmoLatentInfo.Linkage = 0;
	ReloadAmmoLatentInfo.CallbackTarget = this;
	ReloadAmmoLatentInfo.ExecutionFunction = "ReloadAmmoDelay";
	ReloadAmmoLatentInfo.UUID = __LINE__;//行号为ID

	// Fire Delay
	GunFireLatentInfo.Linkage = 0;
	GunFireLatentInfo.CallbackTarget = this;
	GunFireLatentInfo.ExecutionFunction = "GunFireDelay";
	GunFireLatentInfo.UUID = __LINE__;//行号为ID

	// Just for Test
	this->TestInitWeaponData();

	//Blueprint
	BulletDecalClass = LoadClass<ABulletHole>(nullptr, TEXT("Class'/Script/ROTD.BulletHole'"));
	BulletImpactClass = LoadClass<ABulletImpactEffect>(nullptr, TEXT("Class'/Script/ROTD.BulletImpactEffect'"));

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

void AROTDCharacter::SwitchWeapons(int32 Type)
{
	if(IsReloading)
	{
		return;
	}

	switch (Type)
	{
	case 0:
		// 空手
		if (CurrentWeapon) {
			CurrentWeapon->FP_Gun->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));
		}
		CurrentWeapon = EmptyHands;
		break;
	case 1:
		// 匕首
		{
			//if(WeaponMap.Find(EWeapon::EW_Knife) == 0)
			//{
			//	return;
			//}

			if(CurrentWeapon){
				CurrentWeapon->FP_Gun->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));
			}

			CurrentWeapon = WeaponKnife;
			CurrentWeapon->FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Palm_R"));
		}
		break;
	case 2:
		// 手枪
	{
		//if (WeaponMap.Find(EWeapon::EW_Pisto) == 0)
		//{
		//	return;
		//}

		if (CurrentWeapon) {
			CurrentWeapon->FP_Gun->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));
		}

		CurrentWeapon = WeaponPisto;
		CurrentWeapon->FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Pisto_Magnum"));
	}
		break;
	case 3:
		// 冲锋枪
	{	
		//if (WeaponMap.Find(EWeapon::EW_Rifle) == 0)
		//{
		//	return;
		//}

		if (CurrentWeapon) {
			CurrentWeapon->FP_Gun->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepRelative, true));
		}

		CurrentWeapon = WeaponRifle;
		CurrentWeapon->FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Rifle_AK"));
	}
		break;
	case 4:
		// 狙击枪
		//if (WeaponMap.Find(EWeapon::EW_Snipe) == 0)
		//{
		//	return;
		//}

		break;
	default:
		break;
	}
}


void AROTDCharacter::Reload()
{
	if(IsReloading)
	{
		return;
	}

	switch (CurrentWeapon->WeaponType)
	{
	case EWeapon::EW_Hands:
		break;
	case EWeapon::EW_Knife:
		break;
	case EWeapon::EW_Pisto:
	{
		if(CurrentWeapon->GunName == "Magnum")
		{
			IsReloading = true;

			// Play Reload montage
			UAnimMontage* ReloadM = CurrentWeapon->ReloadAnimation;
			if (ReloadM != nullptr)
			{
				CurrentWeapon->FP_Gun->PlayAnimation(ReloadM, false);
			}

			// Load static asset
			FString MagnumReloadMontage = FString(TEXT("AnimMontage'/Game/IBFPSStarterPack/Animations/Arms/ANIM_44_Magnum_Reload_Montage.ANIM_44_Magnum_Reload_Montage'"));
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
		else if(CurrentWeapon->GunName == "Glock")
		{

		}

		break;
	}
	case EWeapon::EW_Rifle:
	{
		if (CurrentWeapon->GunName == "AK47")
		{
			IsReloading = true;
			// Play Reload montage
			UAnimMontage* ReloadAK = CurrentWeapon->ReloadAnimation;
			if (ReloadAK != nullptr)
			{
				CurrentWeapon->FP_Gun->PlayAnimation(ReloadAK, false);
			}

			// Load static asset
			FString AKReloadMontage = FString(TEXT("AnimMontage'/Game/IBFPSStarterPack/Animations/Arms/ANIM_ArK-47_Reload_Montage.ANIM_ArK-47_Reload_Montage'"));
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
		break;
	}
	case EWeapon::EW_Snipe:
	{
		break;
	}
	default:
		break;
	}
}


void AROTDCharacter::OnFire()
{
	if(!CurrentWeapon)
	{
		return;
	}
		
	if(IsReloading)
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
			if (CurrentWeapon->GunName == "NepaleseArmyKnife")
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
					FString assetPath = FString(TEXT("AnimMontage'/Game/IBFPSStarterPack/Animations/Arms/ANIM_Magnum_ADS_Fire_Montage.ANIM_Magnum_ADS_Fire_Montage'"));
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
					FString assetPath = FString(TEXT("AnimMontage'/Game/IBFPSStarterPack/Animations/Arms/ANIM_44_Magnum_Fire_Montage.ANIM_44_Magnum_Fire_Montage'"));
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
		if (CurrentWeapon->GunName == "AK47")
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
					FString assetPath = FString(TEXT("AnimMontage'/Game/IBFPSStarterPack/Animations/Arms/ANIM_ArK-47_ADS-Fire_Montage.ANIM_ArK-47_ADS-Fire_Montage'"));
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
					FString assetPath = FString(TEXT("AnimMontage'/Game/IBFPSStarterPack/Animations/Arms/ANIM_ArK-47_Fire_Montage.ANIM_ArK-47_Fire_Montage'"));
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
		GetWorldTimerManager().SetTimer(AutomaticHandle, this, &AROTDCharacter::OnFire, 0.12f, true);
		break;
	}
	case EWeapon::EW_Snipe:
	{
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

	//if (CurWeaponType == EWeapon::EW_AWP)
	//{
	//	CurrentWeapon->SetHidden(true);
	//}
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

	//if (CurWeaponType == EWeapon::EW_AWP)
	//{
	//	CurrentWeapon->SetHidden(false);
	//}
}

void AROTDCharacter::DropMagazine()
{

}

void AROTDCharacter::InsertMagazine()
{

}

void AROTDCharacter::ReloadMagazine()
{

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
	LatentInfo.UUID = __LINE__;//行号为ID
	UKismetSystemLibrary::Delay(this, 0.1f, LatentInfo);
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


void AROTDCharacter::GunFireDelay()
{
	if (!CurrentWeapon)
	{
		return;
	}

	CanFire = true;
}

void AROTDCharacter::TestInitWeaponData()
{
	UWorld* const World = GetWorld();
	FVector Localtion = FVector(0.f, 0.f, 0.f);
	FRotator Rotator = FRotator(0.f);

	// Empty
	FString HandsStr = GetEmptyHands();
	UClass* EmptyHandsClass = LoadClass<AWeaponBase>(nullptr, *HandsStr);

	if (EmptyHandsClass != nullptr)
	{
		if (World != nullptr)
		{
			EmptyHands = Cast<AWeaponBase>(World->SpawnActor<AWeaponBase>(EmptyHandsClass, Localtion, Rotator));
		}
	}

	// knife
	FString KnifeStr = GetKnife();
	UClass* WeaponKnifeClass = LoadClass<AWeaponBase>(nullptr, *KnifeStr);

	if (WeaponKnifeClass != nullptr)
	{
		if (World != nullptr)
		{
			WeaponKnife = Cast<AWeaponBase>(World->SpawnActor<AWeaponBase>(WeaponKnifeClass, Localtion, Rotator));
		}
	}
	
	// Pisto
	FString PistoStr = GetPisto();
	UClass* WeaponPistoClass = LoadClass<AWeaponBase>(nullptr, *PistoStr);

	if (WeaponPistoClass != nullptr)
	{
		if (World != nullptr)
		{
			WeaponPisto = Cast<AWeaponBase>(World->SpawnActor<AWeaponBase>(WeaponPistoClass, Localtion, Rotator));
		}
	}

	// Rifle
	FString RifleStr = GetRifle();
	UClass* WeaponRifleClass = LoadClass<AWeaponBase>(nullptr, *RifleStr);

	if (WeaponRifleClass != nullptr)
	{
		if (World != nullptr)
		{
			WeaponRifle = Cast<AWeaponBase>(World->SpawnActor<AWeaponBase>(WeaponRifleClass, Localtion, Rotator));
		}
	}

	WeaponMap.Add(EWeapon::EW_Hands, 1);
	WeaponMap.Add(EWeapon::EW_Knife, 1);
	WeaponMap.Add(EWeapon::EW_Pisto, 1);
	WeaponMap.Add(EWeapon::EW_Rifle, 1);
	WeaponMap.Add(EWeapon::EW_Snipe, 0);
}

void AROTDCharacter::OnGunFire()
{
	// Camera Shot
	UCameraComponent* FirstCamera = this->FirstPersonCameraComponent;
	FVector TraceStart = FirstCamera->GetComponentLocation();

	// 子弹精度
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
		// 判断击中的是什么物体，然后生成不同的效果
		//EPhysicalSurface SurfaceType = FShootingUtil::GetInstance()->GetPhysicalSurfaceType(SurfaceType_Default);
		UMaterialInterface* BulletHole = FShootingUtil::GetInstance()->RandomGenerateBulletHole(SurfaceType_Default);
		UNiagaraSystem* ImpactParticle = FShootingUtil::GetInstance()->GetImpactParticleSyatem(SurfaceType_Default);

		UWorld* const World = GetWorld();

		if (BulletDecalClass != nullptr && BulletImpactClass != nullptr)
		{
			if (World != nullptr)
			{
				//ApplyDamageTo(Hit);

				FRotator Rotator1 = UKismetMathLibrary::MakeRotFromX(Hit.ImpactNormal);
				if (BulletHole)
				{
					ABulletHole* BulletDecal = World->SpawnActor<ABulletHole>(BulletDecalClass, Hit.Location, Rotator1);
					BulletDecal->SetBulletHoleMaterial(BulletHole);
				}

				if (ImpactParticle)
				{
					ABulletImpactEffect* BulletImpact = World->SpawnActor<ABulletImpactEffect>(BulletImpactClass, Hit.Location, Rotator1);
					BulletImpact->SetNiagaraSysAsset(ImpactParticle);
				}
			}
		}
	}
}