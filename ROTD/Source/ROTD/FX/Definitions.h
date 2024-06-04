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


// 掉落可捡起物品种类
UENUM()
enum class EItemType : uint8
{
	EItem_Knife,
	EItem_Pisto,
	EItem_Rifle,
	EItem_Snipe,
	EItem_MediaSupply,
	EItem_Flashlight,
	EItem_RifleAmmoSupply,
	EItem_PistoAmmoSupply,
	EItem_ShotgunAmmoSupply,
	EItem_SnifferAmmoSupply
};

// TraceLine 碰撞可交互物品
UENUM()
enum class ETraceLineHitUseType : uint8
{
	EItem_Pickup,
	EItem_Door,
	EItem_Box
};


UCLASS(BlueprintType)
class UROTDItems : public UDataAsset
{
	GENERATED_BODY()
public:
	/** User-visible short name */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FText ItemID;

	/** User-visible short name */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	EItemType ItemType;

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

/** Delegate called when an inventory item changes */
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChangedNative, bool, UROTDItems*);
DECLARE_DELEGATE_TwoParams(FOnInventoryWeaponChanged, bool, UROTDItems*);
