// Fill out your copyright notice in the Description page of Project Settings.


#include "ROTDItemSlot.h"


void UROTDItemSlot::SetItemInfo(FSlateBrush Icon, int Num)
{
	// ��ʾ
	IsEmptySlot = false;
	EquipButton->SetIsEnabled(true);
	ItemImg->SetVisibility(ESlateVisibility::Visible);
	ItemNumBackground->SetVisibility(ESlateVisibility::Visible);
	ItemNum->SetVisibility(ESlateVisibility::Visible);

	// ������Ϣ
	FString sTotal = FString::FromInt(Num);
	ItemNum->SetText(FText::FromString(sTotal));
	ItemImg->SetBrushFromTexture((UTexture2D*)Icon.GetResourceObject());
}

