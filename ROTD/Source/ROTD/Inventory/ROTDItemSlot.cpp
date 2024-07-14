// Fill out your copyright notice in the Description page of Project Settings.


#include "ROTDItemSlot.h"


void UROTDItemSlot::InitBlankSlot(int ItemIndex)
{
	IsEmptySlot = true;
	ItemImg->SetVisibility(ESlateVisibility::Hidden);
	ItemImg->SetVisibility(ESlateVisibility::Hidden);
	ItemNumBackground->SetVisibility(ESlateVisibility::Hidden);
	ItemNum->SetVisibility(ESlateVisibility::Hidden);

	// 格子索引
	this->SlotIndex = ItemIndex;
}

void UROTDItemSlot::SetItemInfo(UROTDItems* Item, int Num, int ItemIndex)
{
	// 物品信息
	this->ItemInfo = Item;

	// 显示
	IsEmptySlot = false;
	ItemImg->SetVisibility(ESlateVisibility::Visible);
	ItemImg->SetVisibility(ESlateVisibility::Visible);
	ItemNumBackground->SetVisibility(ESlateVisibility::Visible);
	ItemNum->SetVisibility(ESlateVisibility::Visible);

	// 设置信息
	FString sTotal = FString::FromInt(Num);
	ItemNum->SetText(FText::FromString(sTotal));
	ItemImg->SetBrushFromTexture((UTexture2D*)Item->ItemIcon.GetResourceObject());

	// 格子索引
	this->SlotIndex = ItemIndex;
}

//void UROTDItemSlot::CreateToolTips()
//{
//	// Init Tip View
//	FString BPItemSlotTipPath = FString(TEXT("WidgetBlueprint'/Game/ROTD/UI/ItemSlotTip_WB.ItemSlotTip_WB_C'"));
//	TSubclassOf<UROTDItemSlotTip> ItemSlotTipClass = LoadClass<UROTDItemSlotTip>(NULL, *BPItemSlotTipPath);
//	ItemSlotTip = CreateWidget<UROTDItemSlotTip>(GetWorld(), ItemSlotTipClass);
//
//	if (ItemSlotTip)
//	{
//		ItemSlotTip->SetItemInfo(Item);
//	}
//}

