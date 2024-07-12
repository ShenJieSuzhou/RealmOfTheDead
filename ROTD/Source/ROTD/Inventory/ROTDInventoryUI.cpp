// Fill out your copyright notice in the Description page of Project Settings.


#include "ROTDInventoryUI.h"
#include "../ROTDPlayerController.h"

void UROTDInventoryUI::InitInventory()
{
	for (int i = 0; i < MaxSlotNum; i++)
	{
		FString BPItemSlotPath = FString(TEXT("WidgetBlueprint'/Game/ROTD/UI/ItemSlot_WB.ItemSlot_WB_C'"));
		TSubclassOf<UROTDItemSlot> ItemSlotClass = LoadClass<UROTDItemSlot>(NULL, *BPItemSlotPath);
		UROTDItemSlot* ItemSlot = CreateWidget<UROTDItemSlot>(GetWorld(), ItemSlotClass);
		if(ItemSlot)
		{
			ItemContainer->AddChild(ItemSlot);
		}
	}
}

void UROTDInventoryUI::ReloadInventory(TArray<UROTDItems*> InventoryItems, TMap<UROTDItems*, int> InventoryData)
{
	if(InventoryItems.Num() > MaxSlotNum)
	{
		// 背包溢出
		return;
	}
	
	int SlotIndex = 0;

	for (UROTDItems* Item : InventoryItems)
	{
		FString ItemId = Item->ItemID.ToString();

		// Filters based on item type
		if (!ItemId.IsEmpty())
		{
			// Item 数量
			const int32* count = InventoryData.Find(Item);
			if(count == 0)
			{
				return;
			}

			// Item icon
			FSlateBrush Icon = Item->ItemIcon;
			if (ItemContainer)
			{
				UROTDItemSlot* ItemSlot = Cast<UROTDItemSlot>(ItemContainer->GetChildAt(SlotIndex));
				ItemSlot->SetItemInfo(Item, *count);
			}
		}
		SlotIndex++;
	}
}

void UROTDInventoryUI::DragAndResort(TArray<UROTDItems*> InventoryItems, int SelectIndex, int DropIndex)
{
	int count = InventoryItems.Num();
	if(SelectIndex > count || DropIndex > count)
	{
		return;
	}

	if(InventoryItems.IsValidIndex(SelectIndex))
	{
		// temp
		UROTDItems* Item = InventoryItems[SelectIndex];
		InventoryItems[SelectIndex] = InventoryItems[DropIndex];
		InventoryItems[DropIndex] = Item;
	}
}

