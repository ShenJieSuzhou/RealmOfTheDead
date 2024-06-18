// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpItemBase.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "Sound/SoundBase.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/Texture2D.h"
#include "NiagaraComponent.h"
#include "WeaponPickup.generated.h"

class USkeletalMeshComponent;
class USceneComponent;
class UAnimMontage;
class USoundBase;

UENUM()
enum class EWeapon : uint8
{
	EW_Hands,
	EW_Knife, //1
	EW_Pisto, //2
	EW_Rifle, //3
	EW_Snipe  //4
};

UENUM(BlueprintType)
enum class ESubWeapon : uint8
{
	EW_Empty,		//0
	EW_Nipol,		//1
	EW_Magnum,		//2
	EW_Glock,		//3
	EW_AK47,		//4
	EW_Remington,	//5
	EW_STEYRSCOUT	//6
};

UCLASS()
class ROTD_API AWeaponPickup : public APickUpItemBase
{
	GENERATED_BODY()
	
public:
	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;
	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UPointLightComponent* FP_PointLight;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* FP_FlashPlane;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UNiagaraComponent* FP_Muzzle;

	// Projectile class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	EWeapon WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	ESubWeapon GunID;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* DryFireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* ReloadDropSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* ReloadInsertSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* ReloadLoadSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimSequence* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* ReloadAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* LowAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* RaiseAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* EquipAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	AActor* BulletShell;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FString GunName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimInstance* WeaponAnimIdleBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float ADSDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float ReloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float BulletSpread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int MagazineVolum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int MagazineBullets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int MaxAmmoCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UROTDItems* Ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool CanScope;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool CanAutomatic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UTexture2D* GunIcon;

public:	
	// Sets default values for this actor's properties
	AWeaponPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "LowLevel")
	void WeaponFire();

	UFUNCTION(BlueprintImplementableEvent, Category = "LowLevel")
	void WeaponReload();

	UFUNCTION(BlueprintImplementableEvent, Category = "LowLevel")
	void BulletShellDrop();

	UFUNCTION(BlueprintImplementableEvent, Category = "LowLevel")
	void WeaponADS();

	UFUNCTION(BlueprintImplementableEvent, Category = "LowLevel")
	void WeaponRecoverADS();
};
