// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "../FX/Definitions.h"

class ROTD_API UROTDInventoryInterface
{
public:
	/** Returns the map of items to data */
	virtual const TMap<UROTDItems*, int>& GetInventoryDataMap() const = 0;

	/** Gets the delegate for inventory item changes */
	virtual FOnInventoryItemChangedNative& GetInventoryItemChangedDelegate() = 0;

	/** Gets the delegate for inventory item changes */
	virtual FOnInventoryWeaponChanged& GetInventoryWeaponChangedDelegate() = 0;
};

