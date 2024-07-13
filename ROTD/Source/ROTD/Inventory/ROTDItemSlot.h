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
#include "ROTDItemSlotTip.h"
#include "ROTDItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class ROTD_API UROTDItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemNum = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* ItemImg = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBorder* ItemNumBackground = nullptr;

	UPROPERTY(BlueprintReadWrite)
	class UROTDItemSlotTip* ItemSlotTip = nullptr;

	UPROPERTY(BlueprintReadWrite)
	UROTDItems* ItemInfo = nullptr;

	bool IsEmptySlot = true;

	UPROPERTY(BlueprintReadWrite)
	int32 SlotIndex;

	void SetItemInfo(UROTDItems* Item, int Num, int ItemIndex);
};

