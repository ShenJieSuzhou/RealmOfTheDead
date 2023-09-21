// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Weapons/WeaponBase.h"
#include "ROTDHealthWeaponWidget.generated.h"

/**
 * 
 */
UCLASS()
class ROTD_API UROTDHealthWeaponWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// ��ɫ������ֵ
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HealthVolumBar;

	// ��ǰ���е��ӵ�
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CurBulletsNum;

	// ��һ�����������ӵ�����
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* BulletsMax;

	// ��ǰ����icon
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* CurWeaponImg;

	// ������ʾ
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TaskDetailStr;

	// ��������ͳ��
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TaskProcess;

	// ��չ��ʾ
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ExtraStr;

public:
	void UpdateAmmo(int currBullets, int TotalBullets);
	
	void SwitchWeapon(AWeaponBase* curWeapon);

	void UpdateHealthProcessBar(float CurrentHealth, float MaxHealth);

private:
	AWeaponBase* DisplayWeapon;
};
