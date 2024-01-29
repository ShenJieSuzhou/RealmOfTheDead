// Fill out your copyright notice in the Description page of Project Settings.


#include "SupplyPickup.h"

// Sets default values
ASupplyPickup::ASupplyPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Supply
	FP_Supply = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Supply"));
	FP_Supply->SetOnlyOwnerSee(false);
	FP_Supply->bCastDynamicShadow = false;
	FP_Supply->CastShadow = false;
	FP_Supply->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASupplyPickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASupplyPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
