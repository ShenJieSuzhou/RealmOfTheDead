// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpItemBase.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "Sound/SoundBase.h"
#include "SupplyPickup.generated.h"

class USkeletalMeshComponent;
class USceneComponent;
class UAnimMontage;
class USoundBase;

UENUM()
enum class ETreatment : uint8
{
	ET_Antivirus // Ç¿Á¦¿¹ÉúËØ
};


UCLASS()
class ROTD_API ASupplyPickup : public APickUpItemBase
{
	GENERATED_BODY()
	
public:
	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* FP_Supply;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* GrabSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* UsedSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* UsedAnimation;

	// Projectile class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	ETreatment TreatmentType;
public:	
	// Sets default values for this actor's properties
	ASupplyPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
