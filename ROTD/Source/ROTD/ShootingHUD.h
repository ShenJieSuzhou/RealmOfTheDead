// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CrossMarkWidget.h"
//#include "Weapons/WeaponBase.h"
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
	UUserWidget* PointWidget;

public:
	AShootingHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	void SetCrossWidgetVisible(bool isVisible);

	void SetPointWidgetVisible(bool isVisible);

	void SetHealthBarWidgetVisible(bool isVisible);

	void UpdateAmmo(int currBullets, int TotalBullets);

	void UpdateMedicalSupply(int Count);

	void SwitchWeapon(UROTDWeaponItem* WeaponItem);

	void UpdateHealth(float CurrentHealth, float MaxHealth);

	UFUNCTION(BlueprintCallable)
	void CanDisplayInteractItemInfo(bool CanDisplay);

	UFUNCTION(BlueprintCallable)
	void UpdateInteractItemInfo(FString Name, FString Detail, int Num);

	UFUNCTION(BlueprintCallable)
	void CanDisplayPressTip(bool CanDisplay);

	UFUNCTION(BlueprintCallable)
	void IsDoorOpen(bool IsOpen);

	UFUNCTION(BlueprintCallable)
	void ShowROTDHUD(bool IsVisible);

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;
};

