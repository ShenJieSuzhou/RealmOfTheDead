// Fill out your copyright notice in the Description page of Project Settings.


#include "ROTDHealthWeaponWidget.h"

void UROTDHealthWeaponWidget::UpdateAmmo(int currBullets, int TotalBullets)
{
	FString sCurrent = FString::FromInt(currBullets);
	CurBulletsNum->SetText(FText::FromString(sCurrent));

	// ���С��10�ţ���ʾ��ɫ
	if(currBullets < 5)
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

	if(curWeapon->WeaponType == EWeapon::EW_Hands)
	{
		CurWeaponImg->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	CurWeaponImg->SetVisibility(ESlateVisibility::Visible);
	this->DisplayWeapon = curWeapon;
	CurWeaponImg->SetBrushFromTexture(curWeapon->GunIcon);
}

void UROTDHealthWeaponWidget::UpdateHealthProcessBar(float CurrentHealth, float MaxHealth)
{
	if(HealthVolumBar == nullptr)
	{
		return;
	}
	
	float percent = CurrentHealth / MaxHealth;

	UE_LOG(LogTemp, Log, TEXT("Health: %f"), percent);

	HealthVolumBar->SetPercent(percent);
}

void UROTDHealthWeaponWidget::CanDisplayInteractDetail(bool CanDisplay)
{
	if(CanDisplay)
	{
		InteractTip->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		InteractTip->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UROTDHealthWeaponWidget::UpdateInteractItemInfo(FString Name, FString Detail, int Num)
{
	InteractItemName->SetText(FText::FromString(Name));

	FString sNum = FString::FromInt(Num);
	InteractItemNum->SetText(FText::FromString("X"+sNum));

	InteractItemType->SetText(FText::FromString(Detail));
}
