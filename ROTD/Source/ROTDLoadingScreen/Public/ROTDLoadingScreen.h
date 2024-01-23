// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleInterface.h"
#include "Slate/DeferredCleanupSlateBrush.h"
#include "Modules/ModuleManager.h"

/** Module interface for this game's loading screens */
class IROTDLoadingScreenModule : public IModuleInterface
{
public:
	/** Loads the module so it can be turned on */
	static inline IROTDLoadingScreenModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IROTDLoadingScreenModule>("ROTDLoadingScreen");
	}

	/** Kicks off the loading screen for in game loading (not startup) */
	//virtual void StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime) = 0;

	/** Stops the loading screen */
	//virtual void StopInGameLoadingScreen() = 0;

	virtual void SetupLoadingMovie(TArray<FString> MoviePaths, float MinimumLoadingScreenDisplayTime = -1.f) = 0;

	virtual void SetupLoadingScreen(class FString Tooltip, float MinimumLoadingScreenDisplayTime = -1.f) = 0;

};
