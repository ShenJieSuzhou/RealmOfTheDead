// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "../FX/Definitions.h"
#include "PickUpItemBase.generated.h"

UCLASS()
class ROTD_API APickUpItemBase : public AActor
{
	GENERATED_BODY()
	
public:
	// Projectile class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 PickUpItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FString PickUpItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UROTDItems *ItemType;

public:	
	// Sets default values for this actor's properties
	APickUpItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
