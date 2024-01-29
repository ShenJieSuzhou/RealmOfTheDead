// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "../FX/Definitions.h"
#include "ROTDWeaponItem.generated.h"

UCLASS()
class ROTD_API UROTDWeaponItem : public UROTDItems
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	UROTDWeaponItem();

	/** Weapon actor to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<AActor> WeaponActor;
};
