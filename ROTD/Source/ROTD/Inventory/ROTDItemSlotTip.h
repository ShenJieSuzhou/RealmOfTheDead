// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "../ROTDItems/ROTDWeaponItem.h"
#include "ROTDItemSlotTip.generated.h"

/**
 * 
 */
UCLASS()
class ROTD_API UROTDItemSlotTip : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UOverlay* FloatDescTip = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemNameText = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* DesText = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemSubText = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CostText = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* ItemBigImage = nullptr;

	UFUNCTION(BlueprintCallable)
	void SetItemInfo(UROTDItems* Item);

	void SetTipSubTitle(EItemType Type);
};
