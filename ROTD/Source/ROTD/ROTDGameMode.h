// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FX/Definitions.h"
#include "ROTDGameMode.generated.h"

UCLASS(minimalapi)
class AROTDGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AROTDGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BulletImpact System")
	FBulletImpact FindBulletImpact(EImpactType Type, bool& success);

	FBulletImpact FindBulletImpact_Implementation(EImpactType Type, bool& success);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BulletImpact System")
	class UBulletImpactData* BulletImpactDataBase;

};



