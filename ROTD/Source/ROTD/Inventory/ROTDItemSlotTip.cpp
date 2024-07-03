// Fill out your copyright notice in the Description page of Project Settings.


#include "ROTDItemSlotTip.h"


void UROTDItemSlotTip::SetItemInfo(UROTDItems* Item)
{
	// Tip name
	ItemNameText->SetText(Item->ItemName);

	// Tip Type
	this->SetTipSubTitle(Item->ItemType);

	// Tip cost
	FString sPrice = FString::FromInt(Item->Price);
	CostText->SetText(FText::FromString(sPrice));

	// Tip icon
	ItemBigImage->SetBrushFromTexture((UTexture2D*)Item->ItemIcon.GetResourceObject());

	// Tip desc
	DesText->SetText(Item->ItemDescription);
}

void UROTDItemSlotTip::SetTipSubTitle(EItemType Type)
{
	switch (Type)
	{
	case EItemType::EItem_Knife:
		ItemSubText->SetText(FText::FromString("��"));
		break;
	case EItemType::EItem_Pisto:
		ItemSubText->SetText(FText::FromString("��ǹ"));
		break;
	case EItemType::EItem_Rifle:
		ItemSubText->SetText(FText::FromString("��ǹ"));
		break;
	case EItemType::EItem_MediaSupply:
		ItemSubText->SetText(FText::FromString("ҩƷ"));
		break;
	case EItemType::EItem_Flashlight:
		ItemSubText->SetText(FText::FromString("���"));
		break;
	case EItemType::EItem_RifleAmmoSupply:
		ItemSubText->SetText(FText::FromString("��ǹ�ӵ�"));
		break;
	case EItemType::EItem_PistoAmmoSupply:
		ItemSubText->SetText(FText::FromString("��ǹ�ӵ�"));
		break;
	case EItemType::EItem_ShotgunAmmoSupply:
		ItemSubText->SetText(FText::FromString("��ǹ�ӵ�"));
		break;
	case EItemType::EItem_SnifferAmmoSupply:
		ItemSubText->SetText(FText::FromString("�ѻ�ǹ�ӵ�"));
		break;
	case EItemType::EItem_Snipe:
		ItemSubText->SetText(FText::FromString("�ѻ�ǹ "));
		break;
	default:
		ItemSubText->SetText(FText::FromString(""));
		break;
	}
}
