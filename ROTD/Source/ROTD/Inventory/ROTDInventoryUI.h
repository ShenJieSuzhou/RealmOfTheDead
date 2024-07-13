// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WrapBox.h"
#include "../ROTDItems/ROTDWeaponItem.h"
#include "ROTDItemSlot.h"
#include "ROTDInventoryUI.generated.h"

/**
 * 
 */
UCLASS()
class ROTD_API UROTDInventoryUI : public UUserWidget
{
	GENERATED_BODY()
	
	// 初始化背包界面
	UFUNCTION(BlueprintCallable)
	void InitInventory();

	UFUNCTION(BlueprintCallable)
	void ReloadInventory(TArray<UROTDItems*> InventoryItems, TMap<UROTDItems*, int> InventoryData);

	// Drop Items 并调整顺序
	UFUNCTION(BlueprintCallable)
	void DragAndResort(int SelectIndex, int DropIndex);
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWrapBox* ItemContainer;

	// 背包最多格数
	int MaxSlotNum = 100;
};
