// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/Button.h"
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

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* EquipButton = nullptr;

	bool IsEmptySlot = true;

	void SetItemInfo(FSlateBrush Icon, int Num);
};
