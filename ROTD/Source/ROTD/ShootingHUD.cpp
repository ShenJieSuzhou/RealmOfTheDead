// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootingHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

AShootingHUD::~AShootingHUD()
{
	CrossWidget = nullptr;
}

AShootingHUD::AShootingHUD()
{

}


void AShootingHUD::DrawHUD()
{
	Super::DrawHUD();
}


void AShootingHUD::BeginPlay()
{
	Super::BeginPlay();

	FString WidgetClassLoadPath = FString(TEXT("WidgetBlueprint'/Game/ROTD/UI/XHair_HUD.XHair_HUD_C'"));
	TSubclassOf<UCrossMarkWidget> CrossWidgetClass = LoadClass<UCrossMarkWidget>(NULL, *WidgetClassLoadPath);
	CrossWidget = CreateWidget<UCrossMarkWidget>(GetWorld(), CrossWidgetClass);
	CrossWidget->AddToViewport();

	FString HealthWeaponPath = FString(TEXT("WidgetBlueprint'/Game/ROTD/UI/Health_Weapon_WB.Health_Weapon_WB_C'"));
	TSubclassOf<UROTDHealthWeaponWidget> HealthWeaponClass = LoadClass<UROTDHealthWeaponWidget>(NULL, *HealthWeaponPath);
	HealthWeaponWidget = CreateWidget<UROTDHealthWeaponWidget>(GetWorld(), HealthWeaponClass);
	HealthWeaponWidget->AddToViewport();
}

void AShootingHUD::SetCrossWidgetVisible(bool isVisible)
{
	if (isVisible)
	{
		CrossWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		CrossWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AShootingHUD::UpdateAmmo(int currBullets, int TotalBullets)
{
	HealthWeaponWidget->UpdateAmmo(currBullets, TotalBullets);
}

void AShootingHUD::SwitchWeapon(AWeaponBase* weapon)
{
	if(weapon == NULL)
	{
		return;
	}

	HealthWeaponWidget->SwitchWeapon(weapon);
}


