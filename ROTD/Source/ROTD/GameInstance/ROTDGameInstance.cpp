// Fill out your copyright notice in the Description page of Project Settings.


#include "ROTDGameInstance.h"

void UROTDGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UROTDGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UROTDGameInstance::EndLoadingScreen);
}

void UROTDGameInstance::BeginLoadingScreen_Implementation(const FString& MapName)
{
	// Only client can show loading view
	if (!IsRunningDedicatedServer())
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;

		if (PlayMovies)
		{
			LoadingScreen.MoviePaths = StringPaths;
		}

		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), LoadingScreenWidget);
		LoadingScreen.WidgetLoadingScreen = Widget->TakeWidget();

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}

void UROTDGameInstance::EndLoadingScreen_Implementation(UWorld* InLoadWorld)
{

}