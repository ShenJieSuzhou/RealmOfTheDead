// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/Border.h"
#include "SupplyPickup.h"
#include "WeaponPickup.h"
#include "ROTDItems/ROTDWeaponItem.h"
#include "ROTDHealthWeaponWidget.generated.h"

/**
 * 
 */
UCLASS()
class ROTD_API UROTDHealthWeaponWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HealthVolumBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CurBulletsNum;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* BulletsMax;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* CurWeaponImg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TaskDetailStr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TaskProcess;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ExtraStr;

	// Interact Tip
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBorder* InteractTip;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock*  InteractItemName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* InteractItemNum;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* InteractItemType;

	// Weapon Panel
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* WeaponPanel;

	// Medical
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UUserWidget* MediaSupply;

public:
	void UpdateAmmo(int currBullets, int TotalBullets);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateAntivirusCount(int Count);

	void SwitchWeapon(UROTDWeaponItem* curWeapon);

	void UpdateHealthProcessBar(float CurrentHealth, float MaxHealth);

	void CanDisplayInteractDetail(bool CanDisplay);

	void UpdateInteractItemInfo(FString Name, FString Detail, int Num);

	void CanShowWeaponPanel(bool CanDisplay);

	void CanShowMedialSlot(bool CanDisplay);

private:
	//AWeaponBase* DisplayWeapon;
};
