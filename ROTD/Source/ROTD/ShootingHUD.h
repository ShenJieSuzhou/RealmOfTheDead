// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CrossMarkWidget.h"
#include "ShootingHUD.generated.h"

UCLASS()
class AShootingHUD : public AHUD
{
	GENERATED_BODY()
	~AShootingHUD();
public:
	UCrossMarkWidget* CrossWidget;
public:
	AShootingHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	void SetCrossWidgetVisible(bool isVisible);

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;
};

