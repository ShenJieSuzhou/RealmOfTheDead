// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ROTD.h"
#include "ROTDItems/ROTDWeaponItem.h"
#include "Inventory/ROTDInventoryInterface.h"
#include "GameFramework/PlayerController.h"
#include "ROTDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ROTD_API AROTDPlayerController : public APlayerController, public UROTDInventoryInterface
{
	GENERATED_BODY()
	
public:
	AROTDPlayerController() {}

	virtual void BeginPlay() override;

	/** Called after the inventory was changed and we notified all delegates */
	void InventoryItemChanged(bool bAdded, UROTDItems* Item);

	// 从存档读取背包数据
	bool ReadDataFromSaveLog();

	// 保存背包数据
	bool SaveInventoryDataToLog();

	// 管理背包数据
	void ManageNewItemInInventory(UROTDItems* NewItem);

	/** Adds a new inventory item, will add it to an empty slot if possible. If the item supports count you can add more than one count. It will also update the level when adding if required */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool AddInventoryItem(UROTDItems* NewItem, int32 ItemCount = 1, bool bAutoSlot = true);

	/** Remove an inventory item, will also remove from slots. A remove count of <= 0 means to remove all copies */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool RemoveInventoryItem(UROTDItems* RemovedItem, int32 RemoveCount = 1);

	/** Returns all inventory items */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool GenInventoryItems();

	/** Returns number of instances of this item found in the inventory. This uses count from GetItemData */
	UFUNCTION(BlueprintPure, Category = Inventory)
	int32 GetInventoryItemCount(UROTDItems* Item) const;

	void DragAndResort(int32 SelectIndex, int32 DropIndex);

	// Implement IRPGInventoryInterface
	virtual const TMap<UROTDItems*, int>& GetInventoryDataMap() const override
	{
		return InventoryData;
	}

	virtual FOnInventoryItemChangedNative& GetInventoryItemChangedDelegate() override
	{
		return OnInventoryItemChangedNative;
	}

	virtual FOnInventoryWeaponChanged& GetInventoryWeaponChangedDelegate() override
	{
		return OnInventoryWeaponChanged;
	}

	/** Calls the inventory update callbacks */
	void NotifyInventoryItemChanged(bool bAdded, UROTDItems* Item);

	// Primary Weapon 
	UROTDItems* PrimaryWeapon;

	// Second Weapon
	UROTDItems* SecondWeapon;

	// Thrid Weapon (Only for sniper)
	UROTDItems* ThridWeapon;

	// Fourth Weapon 
	UROTDItems* FourthWeapon;

	// 管理物品数量映射关系
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UROTDItems*, int> InventoryData;

	// 管理物品数量映射关系
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TMap<UROTDItems*, EItemType> EquipmentsData;

	// 物品背包界面由此数据驱动
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UROTDItems*> InventoryItems;

	// 是否是第一次启动游戏
	bool IsNewStartGame = true;
private:
	/** Delegate called when an inventory item has been added or removed */
	FOnInventoryWeaponChanged OnInventoryWeaponChanged;

	/** Native version above, called before BP delegate */
	FOnInventoryItemChangedNative OnInventoryItemChangedNative;

	int32 MAX_INVENTORY_SLOT = 100;
};
