// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponBase.h"
#include "ShootingHUD.h"
#include "ROTDCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

// Declaration of the delegate that will be called when the Primary Action is triggered
// It is declared as dynamic so it can be accessed also in Blueprints
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseItem);


UCLASS(config=Game)
class AROTDCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	AROTDCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float TurnRateGamepad;

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnUseItem OnUseItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAiming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsReloading;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanFire;
	
	FLatentActionInfo ReloadAmmoLatentInfo;

	FLatentActionInfo GunFireLatentInfo;

	// ������ʱ��
	FTimerHandle AutomaticHandle;

	// Current Weapons
	AWeaponBase* CurrentWeapon;

	// Hands
	AWeaponBase* EmptyHands;
	// Knife
	AWeaponBase* WeaponKnife;
	// Pisto 
	AWeaponBase* WeaponPisto;
	// Rifle
	AWeaponBase* WeaponRifle;
	// Snipe
	AWeaponBase* WeaponSnipe;

	// ��������
	TMap<EWeapon, int32> WeaponMap;

	// ʮ����׼
	AShootingHUD* hud;

protected:
	
	/** Fires a projectile. */
	void OnPrimaryAction();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;

	UClass* BulletDecalClass;

	UClass* BulletImpactClass;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	void MuzzleFlash();

	void ApplyDamageTo(FHitResult Hit);

	UFUNCTION()
	void DelayAndDisplayMuzzle();

	UFUNCTION()
	void ReloadAmmoDelay();

	UFUNCTION()
	void GunFireDelay();

	// �л�����
	UFUNCTION(BlueprintCallable)
	void SwitchWeapons(int32 Type);

	// Reload ��ҩ
	UFUNCTION(BlueprintCallable)
	void Reload();

	// Fire
	UFUNCTION(BlueprintCallable)
	void OnFire();

	UFUNCTION(BlueprintCallable)
	void OnStopFire();

	UFUNCTION(BlueprintCallable)
	void OnAimDownSight();

	UFUNCTION(BlueprintCallable)
	void OnRecoverAimDownSight();

	UFUNCTION(BlueprintCallable)
	void DropMagazine();

	UFUNCTION(BlueprintCallable)
	void InsertMagazine();

	UFUNCTION(BlueprintCallable)
	void CloseCylinder();

	UFUNCTION(BlueprintCallable)
	void ReloadMagazine();

	void OnGunFire();

	FString GetEmptyHands() const { return TEXT("Blueprint'/Game/ROTD/Blueprint/Weapons/Hands_BP.Hands_BP_C'"); }

	FString GetKnife() const { return TEXT("Blueprint'/Game/ROTD/Blueprint/Weapons/NepaleseArmyKnife_BP.NepaleseArmyKnife_BP_C'"); }

	FString GetPisto() const { return TEXT("Blueprint'/Game/ROTD/Blueprint/Weapons/Magnum_BP.Magnum_BP_C'"); }

	FString GetRifle() const { return TEXT("Blueprint'/Game/ROTD/Blueprint/Weapons/AK_BP.AK_BP_C'"); }

	void TestInitWeaponData();

};

