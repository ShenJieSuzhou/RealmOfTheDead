// Copyright Epic Games, Inc. All Rights Reserved.

#include "ROTDGameMode.h"
#include "ROTDCharacter.h"
#include "ShootingHUD.h"
#include "Util/ShootingMaterialUtil.h"
#include "UObject/ConstructorHelpers.h"

AROTDGameMode::AROTDGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	 
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/ROTD/Blueprint/Henry_BP"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AShootingHUD::StaticClass();
}

void AROTDGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	//FShootingMaterialUtil::GetInstance()->GetResLoadDelegate().BindUObject(this, &AROTDGameMode::OnMaterialLoaded);
	//FShootingMaterialUtil::GetInstance()->PreloadMaterials();
}

//void AROTDGameMode::OnMaterialLoaded(bool result)
//{
//	if (result)
//	{
//		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("OnMaterialLoaded Success!"));
//	}
//	else
//	{
//		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("OnMaterialLoaded Failed!"));
//	}
//}

FBulletImpact AROTDGameMode::FindBulletImpact_Implementation(EImpactType Type, bool& success)
{
	success = false;
	FBulletImpact Impact;
	if (BulletImpactDataBase == nullptr)
	{
		// return a default object
		return Impact;
	}

	for(int i = 0; i < BulletImpactDataBase->BulletImpactData.Num(); i++)
	{
		if(BulletImpactDataBase->BulletImpactData[i].Type == Type)
		{
			success = true;
			return BulletImpactDataBase->BulletImpactData[i];
		}
	}

	return Impact;
}
