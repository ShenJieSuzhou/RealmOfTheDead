// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NiagaraFunctionLibrary.h"
#include "Definitions.generated.h"

UENUM()
enum class EImpactType : uint8
{
	EImpact_Default,
	EImpact_Brick,
	EImpact_Wood,
	EImpact_Sand,
	EImpact_Glass,
	EImpact_Concrert,
	EImpact_Skin,
	EImpact_Water,
	EImpact_Plants,
	EImpact_Rubber
};


USTRUCT(BlueprintType)
struct FBulletImpact
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BulletImpact")
	EImpactType Type;

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


UCLASS(BlueprintType)
class UROTDItems : public UDataAsset
{
	GENERATED_BODY()
public:
	/** User-visible short name */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FText ItemName;

	/** User-visible long description */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FText ItemDescription;

	/** Icon to display */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FSlateBrush ItemIcon;

	/** Price in game */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	int32 Price;

	/** Price in game */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	int32 Count;

	/** Maximum number of instances that can be in inventory at once, <= 0 means infinite */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Max)
	int32 MaxCount;
};

