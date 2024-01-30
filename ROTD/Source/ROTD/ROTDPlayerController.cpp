// Fill out your copyright notice in the Description page of Project Settings.


#include "ROTDPlayerController.h"

void AROTDPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AROTDPlayerController::InventoryItemChanged(bool bAdded, UROTDItems* Item)
{

}

bool AROTDPlayerController::AddInventoryItem(UROTDItems* NewItem, int32 ItemCount /*= 1*/, int32 ItemLevel /*= 1*/, bool bAutoSlot /*= true*/)
{
	

	return true;
}

bool AROTDPlayerController::RemoveInventoryItem(UROTDItems* RemovedItem, int32 RemoveCount /*= 1*/)
{
	return true;
}

void AROTDPlayerController::GetInventoryItems(TArray<UROTDItems*>& Items)
{

}

int32 AROTDPlayerController::GetInventoryItemCount(UROTDItems* Item) const
{
	return 0;
}

bool AROTDPlayerController::GetInventoryItemData(UROTDItems* Item, int& Count) const
{
	return true;
}

void AROTDPlayerController::NotifyInventoryItemChanged(bool bAdded, UROTDItems* Item)
{

}

