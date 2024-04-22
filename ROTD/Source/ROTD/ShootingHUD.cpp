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

	
}

void AShootingHUD::ShowROTDHUD(bool IsVisible)
{
	FString WidgetClassLoadPath = FString(TEXT("WidgetBlueprint'/Game/ROTD/UI/XHair_HUD.XHair_HUD_C'"));
	TSubclassOf<UCrossMarkWidget> CrossWidgetClass = LoadClass<UCrossMarkWidget>(NULL, *WidgetClassLoadPath);
	CrossWidget = CreateWidget<UCrossMarkWidget>(GetWorld(), CrossWidgetClass);
	CrossWidget->AddToViewport();
	CrossWidget->SetVisibility(ESlateVisibility::Hidden);

	// Point 
	FString WidgetPointPath = FString(TEXT("WidgetBlueprint'/Game/ROTD/UI/XCircle_HUD.XCircle_HUD_C'"));
	TSubclassOf<UUserWidget> PointWidgetClass = LoadClass<UUserWidget>(NULL, *WidgetPointPath);
	PointWidget = CreateWidget<UUserWidget>(GetWorld(), PointWidgetClass);
	PointWidget->AddToViewport();

	FString HealthWeaponPath = FString(TEXT("WidgetBlueprint'/Game/ROTD/UI/Health_Weapon_WB.Health_Weapon_WB_C'"));
	TSubclassOf<UROTDHealthWeaponWidget> HealthWeaponClass = LoadClass<UROTDHealthWeaponWidget>(NULL, *HealthWeaponPath);
	HealthWeaponWidget = CreateWidget<UROTDHealthWeaponWidget>(GetWorld(), HealthWeaponClass);
	HealthWeaponWidget->AddToViewport();
}

void AShootingHUD::SetCrossWidgetVisible(bool isVisible)
{
	if(CrossWidget == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("CrossWidget ")));
		return;
	}
	if (isVisible)
	{
		CrossWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		CrossWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AShootingHUD::SetPointWidgetVisible(bool isVisible)
{
	if (PointWidget == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("PointWidget ")));
		return;
	}
	if (isVisible)
	{
		PointWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PointWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AShootingHUD::SetHealthBarWidgetVisible(bool isVisible)
{
	if (HealthWeaponWidget == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("HealthWeaponWidget ")));
		return;
	}
	if (isVisible)
	{
		HealthWeaponWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		HealthWeaponWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AShootingHUD::UpdateAmmo(int currBullets, int TotalBullets)
{
	HealthWeaponWidget->UpdateAmmo(currBullets, TotalBullets);
}

void AShootingHUD::UpdateMedicalSupply(int Count)
{
	
	HealthWeaponWidget->UpdateAntivirusCount(Count);
}

void AShootingHUD::SwitchWeapon(UROTDWeaponItem* WeaponItem)
{
	if(WeaponItem == NULL)
	{
		return;
	}
	
	HealthWeaponWidget->CanShowWeaponPanel(true);
	HealthWeaponWidget->SwitchWeapon(WeaponItem);
}

void AShootingHUD::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	HealthWeaponWidget->UpdateHealthProcessBar(CurrentHealth, MaxHealth);
}

void AShootingHUD::CanDisplayInteractItemInfo(bool CanDisplay)
{
	HealthWeaponWidget->CanDisplayInteractDetail(CanDisplay);
}

void AShootingHUD::UpdateInteractItemInfo(FString Name, FString Detail, int Num)
{
	HealthWeaponWidget->UpdateInteractItemInfo(Name, Detail, Num);
}

void AShootingHUD::CanDisplayPressTip(bool CanDisplay)
{
	HealthWeaponWidget->CanShowPressTip(CanDisplay);
}

void AShootingHUD::IsDoorOpen(bool IsOpen)
{
	HealthWeaponWidget->IsDoorOpen(IsOpen);
}