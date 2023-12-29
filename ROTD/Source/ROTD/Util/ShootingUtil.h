// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Chaos/ChaosEngineInterface.h"
#include "../GameConfig/ShootingConfigs.h"
#include "ShootingMaterialUtil.h"
#include "../FX/Definitions.h"
#include "Math/UnrealMathUtility.h"

class FShootingUtil
{
public:
	static FShootingUtil* GetInstance()
	{
		static FShootingUtil sFShootingUtil;
		return &sFShootingUtil;
	}

	
	EImpactType GetImpactType(UPhysicalMaterial* material);

	EPhysicalSurface GetPhysicalSurfaceType(UPhysicalMaterial* material);

	UMaterialInterface* RandomGenerateBulletHole(EPhysicalSurface type);

	UNiagaraSystem* GetImpactParticleSyatem(EPhysicalSurface type);
};