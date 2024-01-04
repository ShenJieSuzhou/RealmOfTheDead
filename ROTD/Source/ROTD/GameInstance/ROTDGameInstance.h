// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Runtime/UMG/Public/UMG.h"
#include "MoviePlayer.h"
#include "ROTDGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ROTD_API UROTDGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (DisplayName = "BeginLoadingScreen"), Category = "Loading Screen")
	void BeginLoadingScreen(const FString& MapName);
	void BeginLoadingScreen_Implementation(const FString& MapName);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (DisplayName = "EndLoadingScreen"), Category = "Loading Screen")
	void EndLoadingScreen(UWorld* InLoadWorld);
	void EndLoadingScreen_Implementation(UWorld* InLoadWorld);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading Screen")
	TSubclassOf<class UUserWidget> LoadingScreenWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading Screen")
	bool PlayMovies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading Screen")
	TArray<FString> StringPaths;
};
