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

	// ���ݲ��ʻ�ȡ��Ӧ������ͼ
	TArray<FSoftObjectPath> GetBulletDecalWithType(EPhysicalSurface type);

	// ���ݲ��ʻ�ȡ��Ӧ����
	FString GetParticleSystemWithType(EPhysicalSurface type);

	// ���ݲ��ʻ�ȡ��Ӧ����ͼ·��
	FString GetBPClassPathWithType(EPhysicalSurface type);
};

