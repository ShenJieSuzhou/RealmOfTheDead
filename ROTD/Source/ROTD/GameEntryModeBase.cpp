// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEntryModeBase.h"

AGameEntryModeBase::AGameEntryModeBase()
{

}

void AGameEntryModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AGameEntryModeBase::StartPlay()
{
	Super::StartPlay();
}

void AGameEntryModeBase::PreLoadMaterials()
{
	FShootingMaterialUtil::GetInstance()->GetResLoadDelegate().BindUObject(this, &AGameEntryModeBase::OnMaterialLoaded);
	FShootingMaterialUtil::GetInstance()->PreloadMaterials();
}


void AGameEntryModeBase::OnMaterialLoaded(bool result)
{
	if (result)
	{
		// ���� Loading ������ StartGame ��ť
		AssetsLoadComplete();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("22222"));
	}
}