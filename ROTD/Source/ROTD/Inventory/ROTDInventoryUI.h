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
	
	// ��ʼ����������
	UFUNCTION(BlueprintCallable)
	void InitInventory();

	UFUNCTION(BlueprintCallable)
	void ReloadInventory(TMap<UROTDItems*, int> InventoryData);

	// Drop Items ������˳��
	void DragAndResort();
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWrapBox* ItemContainer;

	// ����������
	int MaxSlotNum = 100;
};