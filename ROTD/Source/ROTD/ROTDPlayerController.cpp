// Fill out your copyright notice in the Description page of Project Settings.


#include "ROTDPlayerController.h"

void AROTDPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AROTDPlayerController::InventoryItemChanged(bool bAdded, UROTDItems* Item)
{

}

bool AROTDPlayerController::AddInventoryItem(UROTDItems* NewItem, int32 ItemCount /*= 1*/, bool bAutoSlot /*= true*/)
{
	bool bChanged = false;
	if (!NewItem)
	{
		UE_LOG(LogROTD, Warning, TEXT("AddInventoryItem: Failed trying to add null item!"));
		return false;
	}

	if (ItemCount <= 0)
	{
		UE_LOG(LogROTD, Warning, TEXT("AddInventoryItem: Failed trying to add item %s with negative count!"), *NewItem->GetName());
		return false;
	}

	// Find current item data, which may be empty
	int OldCount = GetInventoryItemCount(NewItem);

	// 判断能否添加，是否数量已到最大值
	if(OldCount >= NewItem->MaxCount)
	{
		UE_LOG(LogROTD, Warning, TEXT("AddInventoryItem: Item reach maxcount!"));
		return false;
	}

	// 是什么类型的物品
	if(NewItem->ItemType == EItemType::EItem_Rifle)
	{
		PrimaryWeapon = NewItem;
	}
	else if(NewItem->ItemType == EItemType::EItem_Pisto)
	{
		SecondWeapon = NewItem;
	}
	else if(NewItem->ItemType == EItemType::EItem_Snipe)
	{
		ThridWeapon = NewItem;
	}
	else if (NewItem->ItemType == EItemType::EItem_Knife)
	{
		FourthWeapon = NewItem;
	}

	// Find modified data
	int NewCount = OldCount + ItemCount;

	if (OldCount != NewCount)
	{
		// If data changed, need to update storage and call callback
		InventoryData.Add(NewItem, NewCount);
		NotifyInventoryItemChanged(true, NewItem);
		bChanged = true;
	}

	if (bAutoSlot)
	{
		// Slot item if required
	}

	if (bChanged)
	{
		// If anything changed, write to save game
		return true;
	}

	return false;
}

bool AROTDPlayerController::RemoveInventoryItem(UROTDItems* RemovedItem, int32 RemoveCount /*= 1*/)
{
	if (!RemovedItem)
	{
		UE_LOG(LogROTD, Warning, TEXT("RemoveInventoryItem: Failed trying to remove null item!"));
		return false;
	}

	// Find current item data, which may be empty
	int ItemCount = GetInventoryItemCount(RemovedItem);;

	if (ItemCount <= 0)
	{
		// Wasn't found
		return false;
	}

	// 是什么类型的物品
	if (RemovedItem->ItemType == EItemType::EItem_Rifle)
	{
		delete PrimaryWeapon;
		PrimaryWeapon = NULL;
	}
	else if (RemovedItem->ItemType == EItemType::EItem_Pisto)
	{
		delete SecondWeapon;
		SecondWeapon = NULL;
	}
	else if (RemovedItem->ItemType == EItemType::EItem_Snipe)
	{
		delete ThridWeapon;
		ThridWeapon = NULL;
	}
	else if (RemovedItem->ItemType == EItemType::EItem_Knife)
	{
		delete FourthWeapon;
		FourthWeapon = NULL;
	}

	// If RemoveCount <= 0, delete all
	if (RemoveCount <= 0)
	{
		ItemCount = 0;
	}
	else
	{
		ItemCount -= RemoveCount;
	}

	if (ItemCount > 0)
	{
		// Update data with new count
		InventoryData.Add(RemovedItem, ItemCount);
	}
	else
	{
		// Remove item entirely, make sure it is unslotted
		InventoryData.Remove(RemovedItem);
	}

	// If we got this far, there is a change so notify and save
	NotifyInventoryItemChanged(false, RemovedItem);
	return true;
}

void AROTDPlayerController::GetInventoryItems(TArray<UROTDItems*>& Items)
{
	for (const TPair<UROTDItems*, int>& Pair : InventoryData)
	{
		if (Pair.Key)
		{
			FString ItemId = Pair.Key->ItemID.ToString();

			// Filters based on item type
			if (!ItemId.IsEmpty())
			{
				Items.Add(Pair.Key);
			}
		}
	}
}

int32 AROTDPlayerController::GetInventoryItemCount(UROTDItems* Item) const
{
	int Count = *InventoryData.Find(Item);

	if (Count > 0)
	{
		return Count;
	}
	return 0;
}

void AROTDPlayerController::NotifyInventoryItemChanged(bool bAdded, UROTDItems* Item)
{
	// Notify native before blueprint
	// 通知 character 切换武器（刀，手枪，AK）
	OnInventoryItemChangedNative.Broadcast(bAdded, Item);
	OnInventoryItemChanged.Broadcast(bAdded, Item);
}

