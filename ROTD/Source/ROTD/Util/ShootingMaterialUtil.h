// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Chaos/ChaosEngineInterface.h"
#include "Materials/MaterialInstanceConstant.h"
#include "NiagaraComponent.h"
#include "../GameConfig/ShootingConfigs.h"
#include "Math/UnrealMathUtility.h"

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
	// �첽���ص�����Դ
	void RequestAsyncLoad(FString MaterialPath);

	// ͬ������������Դ
	bool RequestSyncLoad(TArray<FSoftObjectPath> ResToLoad, TArray<UObject*>& Resources);

	// ͬ��������Դ
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