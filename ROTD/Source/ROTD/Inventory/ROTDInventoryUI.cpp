// Fill out your copyright notice in the Description page of Project Settings.


#include "ROTDInventoryUI.h"

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

void UROTDInventoryUI::ReloadInventory(TMap<UROTDItems*, int> InventoryData)
{
	if(InventoryData.Num() > MaxSlotNum)
	{
		// 背包溢出
		return;
	}
	
	int SlotIndex = 0;
	for (const TPair<UROTDItems*, int>& Pair : InventoryData)
	{
		if (Pair.Key)
		{
			FString ItemId = Pair.Key->ItemID.ToString();

			// Filters based on item type
			if (!ItemId.IsEmpty())
			{
				// Item 数量
				int count = Pair.Value;
				// Item icon
				FSlateBrush Icon = Pair.Key->ItemIcon;
				if (ItemContainer)
				{
					UROTDItemSlot* ItemSlot = Cast<UROTDItemSlot>(ItemContainer->GetChildAt(SlotIndex));
					ItemSlot->SetItemInfo(Pair.Key, count);
				}
			}
			SlotIndex++;
		}
	}
}

void UROTDInventoryUI::DragAndResort()
{

}

//if (Pair.Key)
//{
//	FString ItemId = Pair.Key->ItemID.ToString();

//	// Filters based on item type
//	if (!ItemId.IsEmpty())
//	{

//		// Make ItemSlot 显示


//		ItemContainer->AddChild(ItemSlot);
//	}