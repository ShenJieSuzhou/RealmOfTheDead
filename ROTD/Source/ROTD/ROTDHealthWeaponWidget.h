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
	// 角色的生命值
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HealthVolumBar;

	// 当前弹夹的子弹
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CurBulletsNum;

	// 这一类型武器的子弹总量
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* BulletsMax;

	// 当前武器icon
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* CurWeaponImg;

	// 任务提示
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TaskDetailStr;

	// 任务数字统计
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TaskProcess;

	// 扩展显示
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ExtraStr;

public:
	void UpdateAmmo(int currBullets, int TotalBullets);
	
	void SwitchWeapon(AWeaponBase* curWeapon);

private:
	AWeaponBase* DisplayWeapon;
};
