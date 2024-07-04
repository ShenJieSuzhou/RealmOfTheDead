// Fill out your copyright notice in the Description page of Project Settings.


#include "ROTDItemSlot.h"


void UROTDItemSlot::SetItemInfo(UROTDItems* Item, int Num)
{
	// ��Ʒ��Ϣ
	this->ItemInfo = Item;

	// ��ʾ
	IsEmptySlot = false;
	EquipButton->SetIsEnabled(true);
	ItemImg->SetVisibility(ESlateVisibility::Visible);
	ItemNumBackground->SetVisibility(ESlateVisibility::Visible);
	ItemNum->SetVisibility(ESlateVisibility::Visible);

	// ������Ϣ
	FString sTotal = FString::FromInt(Num);
	ItemNum->SetText(FText::FromString(sTotal));
	ItemImg->SetBrushFromTexture((UTexture2D*)Item->ItemIcon.GetResourceObject());
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
