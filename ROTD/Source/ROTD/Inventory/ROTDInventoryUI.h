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

	// 刷新背包
	UFUNCTION(BlueprintCallable)
	void UpdateInventory(TArray<UROTDItems*> InventoryItems);

	// Drag Items 并调整顺序
	UFUNCTION(BlueprintCallable)
	void DragAndResort(int SelectIndex, int DropIndex);

	// Drop Item
	UFUNCTION(BlueprintCallable)
	int DropItem(int DropIndex);

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWrapBox* ItemContainer;

	// 背包最多格数
	int MaxSlotNum = 100;
};
