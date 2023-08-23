// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ROTDGameMode.generated.h"

UCLASS(minimalapi)
class AROTDGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AROTDGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);

	UFUNCTION()
	void OnMaterialLoaded(bool result);
};



