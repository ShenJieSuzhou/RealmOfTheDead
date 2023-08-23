// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chaos/ChaosEngineInterface.h"

class FShootingConfigs
{
public:
	static FShootingConfigs* GetInstance()
	{
		static FShootingConfigs sFShootConfigs;
		return &sFShootConfigs;
	}

	// 根据材质获取对应弹孔贴图
	TArray<FSoftObjectPath> GetBulletDecalWithType(EPhysicalSurface type);

	// 根据材质获取对应粒子
	FString GetParticleSystemWithType(EPhysicalSurface type);

	// 根据材质获取对应的蓝图路径
	FString GetBPClassPathWithType(EPhysicalSurface type);
};

