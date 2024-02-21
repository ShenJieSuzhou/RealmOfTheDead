// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PickupItems/WeaponPickup.h"
#include "ROTDItems/ROTDSupplyItem.h"
#include "ShootingHUD.h"
#include "NiagaraFunctionLibrary.h"
#include "ROTDPlayerController.h"
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

public:
	AROTDCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
		USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;

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

	FLatentActionInfo TreatmentLatentInfo;

	FTimerHandle AutomaticHandle;

	// Current Weapons
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	AWeaponPickup* CurrentWeapon;

	// Medial Supple
	UROTDSupplyItem* AntiVirusSupply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WeaponType;

	AShootingHUD* hud;

	// Primary Weapon 
	AWeaponPickup* PrimaryWeapon = NULL;

	// Second Weapon
	AWeaponPickup* SecondWeapon = NULL;

	// Thrid Weapon (Only for sniper)
	AWeaponPickup* ThridWeapon = NULL;

	// Fourth Weapon 
	AWeaponPickup* FourthWeapon = NULL;

	AROTDPlayerController* PlayerController;

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

	// Cache MedicalSupply
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	ASupplyPickup* MedicalSupply = NULL;	
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

	void ShellEjection();

	UFUNCTION()
	void DelayAndDisplayMuzzle();

	UFUNCTION()
	void ReloadAmmoDelay();

	UFUNCTION()
	void TreatmentDelay();

	UFUNCTION()
	void GunFireDelay();

	// Weapon Pack
	void PickUpWeapons(bool IsAdded, UROTDItems* Item);
	// ItemChanged, like bullet, medical supply 
	void InventoryItemChanged(bool IsAdded, UROTDItems* Item);

	// Reload 
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

	UFUNCTION(BlueprintCallable)
	void UpdatePlayerHealth(float CurrentHealth, float MaxHealth);

	UFUNCTION(BlueprintCallable)
	void PlayerDieAndHideCross();

	UFUNCTION(BlueprintCallable)
	void DropWeaponAndSwitchWeapon();

	void OnGunFire();

	UFUNCTION(BlueprintCallable)
	void SwitchWeapons(EWeapon CurrWeaponType);

	UFUNCTION(BlueprintCallable)
	void TreatSelf(EWeapon CurrWeaponType);

	void EquipWeapon(AWeaponPickup* Weapon);
};

