// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NiagaraFunctionLibrary.h"
#include "Definitions.generated.h"

USTRUCT(BlueprintType)
struct FBulletImpact
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BulletImpact")
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BulletImpact")
	TWeakObjectPtr<class UPhysicalMaterial> PhysMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BulletImpact")
	TArray<UMaterialInterface*> BulletDecals;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BulletImpact")
	UNiagaraSystem* ImpactNiagara;
};

UCLASS(BlueprintType)
class UBulletImpactData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BulletImpact")
	TArray<FBulletImpact> BulletImpactData;
};

