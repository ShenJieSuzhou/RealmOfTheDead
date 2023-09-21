// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CrossMarkWidget.h"
#include "Weapons/WeaponBase.h"
#include "ROTDHealthWeaponWidget.h"
#include "ShootingHUD.generated.h"

UCLASS()
class AShootingHUD : public AHUD
{
	GENERATED_BODY()
	~AShootingHUD();
public:
	UCrossMarkWidget* CrossWidget;
	UROTDHealthWeaponWidget* HealthWeaponWidget;

public:
	AShootingHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	void SetCrossWidgetVisible(bool isVisible);

	void UpdateAmmo(int currBullets, int TotalBullets);

	void SwitchWeapon(AWeaponBase* weapon);

	void UpdateHealth(float CurrentHealth, float MaxHealth);

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;
};

