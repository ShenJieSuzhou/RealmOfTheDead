// Fill out your copyright notice in the Description page of Project Settings.


#include "ROTDHealthWeaponWidget.h"

void UROTDHealthWeaponWidget::UpdateAmmo(int currBullets, int TotalBullets)
{
	FString sCurrent = FString::FromInt(currBullets);
	CurBulletsNum->SetText(FText::FromString(sCurrent));

	// 如果小于10颗，显示红色
	if(currBullets < 10)
	{
		FSlateColor newColor = FSlateColor(FLinearColor(255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 1.0f));
		CurBulletsNum->SetColorAndOpacity(newColor);
	}
	else
	{
		FSlateColor newColor = FSlateColor(FLinearColor(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f));
		CurBulletsNum->SetColorAndOpacity(newColor);
	}

	FString sTotal = FString::FromInt(TotalBullets);
	BulletsMax->SetText(FText::FromString(sTotal));
}

void UROTDHealthWeaponWidget::SwitchWeapon(AWeaponBase* curWeapon)
{
	if(curWeapon == NULL)
	{
		//UE_LOG(LogTemp, Log, "Weapon cannot be null");
		return;
	}

	this->DisplayWeapon = curWeapon;

}
