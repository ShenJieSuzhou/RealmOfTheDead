// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Chaos/ChaosEngineInterface.h"
#include "Materials/MaterialInstanceConstant.h"
#include "NiagaraComponent.h"
#include "../GameConfig/ShootingConfigs.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

/**
 * ��Դ���ػص�
 */
DECLARE_DELEGATE_OneParam(FMaterialLoadDelegate, bool);

class FShootingMaterialUtil
{
public:
	static FShootingMaterialUtil* GetInstance()
	{
		static FShootingMaterialUtil sMaterialUtil;
		return &sMaterialUtil;
	}

	// Ԥ���ز���
	void PreloadMaterials();

	FMaterialLoadDelegate& GetResLoadDelegate();

	// Common 
	void CommonMaterialDeferred();

	// Metal
	void MetalMaterialDeferred();

	// Wood
	void WoodMaterialDeferred();

	// Water
	void WaterMaterialDeferred();

	// Water
	void SandMaterialDeferred();
	
	// BrickMaterial
	void BrickMaterialDeferred();

	// GlassMaterial
	void GlassMaterialDeferred();

	// GroundMaterial
	void GroundMaterialDeferred();

	// Nigara Asset
	void defaultVFDeferred();

	void MetalVFDeferred();

	void WoodVFDeferred();

	void WaterVFDeferred();

	void SandVFDeferred();

	void BrickVFDeferred();

	void GlassVFDeferred();

	void GroundVFDeferred();

	void BloodVFDeferred();
	
	// Check assets is loaded 
	void CheckGameResLoad();

public:
	TArray<FSoftObjectPath> CommonMaterial;
	
	TArray<FSoftObjectPath> MetalMaterial;
	
	TArray<FSoftObjectPath> WoodMaterial;

	TArray<FSoftObjectPath> WaterMaterial;

	TArray<FSoftObjectPath> SandMaterial;

	TArray<FSoftObjectPath> BrickMaterial;

	TArray<FSoftObjectPath> GlassMaterial;

	TArray<FSoftObjectPath> GroundMaterial;

	FSoftObjectPath defaultVF;
	FSoftObjectPath MetalVF;
	FSoftObjectPath WoodVF;
	FSoftObjectPath WaterVF;
	FSoftObjectPath SandVF;
	FSoftObjectPath BrickVF;
	FSoftObjectPath GlassVF;
	FSoftObjectPath GroundVF;
	FSoftObjectPath BloodVF;
public:
	TArray<UObject*> GetBulletsWood();
	TArray<UObject*> GetBulletsMetal();
	TArray<UObject*> GetBulletsCommon();
	TArray<UObject*> GetBulletsGlass();
	TArray<UObject*> GetBulletsSand();
	TArray<UObject*> GetBulletsBrick();
	TArray<UObject*> GetBulletsGround();
	TArray<UObject*> GetBulletsWater();

	UObject* GetVFWood();
	UObject* GetVFMetal();
	UObject* GetVFCommon();
	UObject* GetVFGlass();
	UObject* GetVFSand();
	UObject* GetVFBrick();
	UObject* GetVFGround();
	UObject* GetVFWater();
	UObject* GetVFBlood();

private:
	// Async load game assets
	bool RequestAsyncLoad(TArray<FSoftObjectPath> ResToLoad, FStreamableDelegate DelegateToCall);

	bool RequestAsyncLoadSingle(FSoftObjectPath, FStreamableDelegate DelegateToCall);

	// Sync load game assets
	bool RequestSyncLoad(TArray<FSoftObjectPath> ResToLoad, TArray<UObject*>& Resources);

	bool RequestSyncLoadOne(FSoftObjectPath ResToLoad, UObject*& Resource);

private:
	TArray<UObject*> BulletsGlass;

	TArray<UObject*> BulletsGround;

	TArray<UObject*> BulletsWood;

	TArray<UObject*> BulletsMetal;
	 
	TArray<UObject*> BulletsWater;

	TArray<UObject*> BulletsSand;

	TArray<UObject*> BulletsCommon;

	TArray<UObject*> BulletsBrick;

	TArray<UObject*> Knife;

	UObject* VF_Default;

	UObject* VF_Ground;

	UObject* VF_Wood;

	UObject* VF_Glass;

	UObject* VF_Metal;

	UObject* VF_Water;

	UObject* VF_Sand;

	UObject* VF_Common;

	UObject* VF_Brick;

	UObject* VF_Blood;

	UObject* VF_Knife;

	FMaterialLoadDelegate ResLoadDelegate;
};