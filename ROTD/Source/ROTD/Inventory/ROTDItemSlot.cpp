// Fill out your copyright notice in the Description page of Project Settings.


#include "ROTDItemSlot.h"


void UROTDItemSlot::SetItemInfo(FSlateBrush Icon, int Num)
{
	// 显示
	IsEmptySlot = false;
	EquipButton->SetIsEnabled(true);
	ItemImg->SetVisibility(ESlateVisibility::Visible);
	ItemNumBackground->SetVisibility(ESlateVisibility::Visible);
	ItemNum->SetVisibility(ESlateVisibility::Visible);

	// 设置信息
	FString sTotal = FString::FromInt(Num);
	ItemNum->SetText(FText::FromString(sTotal));
	ItemImg->SetBrushFromTexture((UTexture2D*)Icon.GetResourceObject());
}

