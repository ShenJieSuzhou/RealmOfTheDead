// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickup.h"

// Sets default values
AWeaponPickup::AWeaponPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Gun
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false);
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetupAttachment(RootComponent);

	// Set MuzzleLocation
	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	
	// Set PointLight
	FP_PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	FP_PointLight->SetIntensity(0);
	FP_PointLight->SetupAttachment(FP_Gun);

	// SetPlane
	FP_FlashPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunFlash"));
	FP_FlashPlane->SetVisibility(false);
	FP_FlashPlane->SetupAttachment(FP_Gun);

	FP_Muzzle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MuzzleFlash"));
	FP_Muzzle->SetVisibility(false);
	FP_Muzzle->AttachToComponent(FP_Gun, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Fire_FX_Slot"));
}

// Called when the game starts or when spawned
void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
