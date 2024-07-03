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
		ItemSubText->SetText(FText::FromString("µ¶"));
		break;
	case EItemType::EItem_Pisto:
		ItemSubText->SetText(FText::FromString("ÊÖÇ¹"));
		break;
	case EItemType::EItem_Rifle:
		ItemSubText->SetText(FText::FromString("²½Ç¹"));
		break;
	case EItemType::EItem_MediaSupply:
		ItemSubText->SetText(FText::FromString("Ò©Æ·"));
		break;
	case EItemType::EItem_Flashlight:
		ItemSubText->SetText(FText::FromString("Åä¼þ"));
		break;
	case EItemType::EItem_RifleAmmoSupply:
		ItemSubText->SetText(FText::FromString("²½Ç¹×Óµ¯"));
		break;
	case EItemType::EItem_PistoAmmoSupply:
		ItemSubText->SetText(FText::FromString("ÊÖÇ¹×Óµ¯"));
		break;
	case EItemType::EItem_ShotgunAmmoSupply:
		ItemSubText->SetText(FText::FromString("ÁÔÇ¹×Óµ¯"));
		break;
	case EItemType::EItem_SnifferAmmoSupply:
		ItemSubText->SetText(FText::FromString("¾Ñ»÷Ç¹×Óµ¯"));
		break;
	case EItemType::EItem_Snipe:
		ItemSubText->SetText(FText::FromString("¾Ñ»÷Ç¹ "));
		break;
	default:
		ItemSubText->SetText(FText::FromString(""));
		break;
	}
}
