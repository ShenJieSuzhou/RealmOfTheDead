// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "./Util/ShootingMaterialUtil.h"
#include "GameEntryModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ROTD_API AGameEntryModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGameEntryModeBase();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void StartPlay() override;

public:
	// Loading static Assets
	UFUNCTION(BlueprintCallable, Category = "Mainmenu")
	void PreLoadMaterials();

	UFUNCTION()
	void OnMaterialLoaded(bool result);

	// ��Դ�������
	UFUNCTION(BlueprintImplementableEvent, Category = "Mainmenu")
	void AssetsLoadComplete();
};
