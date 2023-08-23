// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Chaos/ChaosEngineInterface.h"
#include "../GameConfig/ShootingConfigs.h"
#include "ShootingMaterialUtil.h"
#include "Math/UnrealMathUtility.h"

class FShootingUtil
{
public:
	static FShootingUtil* GetInstance()
	{
		static FShootingUtil sFShootingUtil;
		return &sFShootingUtil;
	}

	// 获取击中的材质
	EPhysicalSurface GetPhysicalSurfaceType(UPhysicalMaterial* material);

	// 根据材质随机生成弹孔
	UMaterialInterface* RandomGenerateBulletHole(EPhysicalSurface type);

	// 获取击中粒子效果
	UNiagaraSystem* GetImpactParticleSyatem(EPhysicalSurface type);
};