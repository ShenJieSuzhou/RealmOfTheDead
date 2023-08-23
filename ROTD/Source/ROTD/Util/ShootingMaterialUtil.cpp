// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingMaterialUtil.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

void FShootingMaterialUtil::PreloadMaterials()
{	
	// 同步加载资源
	TArray<FSoftObjectPath> CommonMaterial = FShootingConfigs::GetInstance()->GetBulletDecalWithType(SurfaceType_Default);
	if(!RequestSyncLoad(CommonMaterial, BulletsCommon))
	{
		ResLoadDelegate.ExecuteIfBound(false);
		return;
	}

	/*TArray<FSoftObjectPath> MatelMaterial = FShootingConfigs::GetInstance()->GetBulletDecalWithType(SurfaceType1);
	if(!RequestSyncLoad(MatelMaterial, BulletsMetal))
	{
		ResLoadDelegate.ExecuteIfBound(false);
		return;
	}

	TArray<FSoftObjectPath> WoodMaterial = FShootingConfigs::GetInstance()->GetBulletDecalWithType(SurfaceType2);
	if (!RequestSyncLoad(WoodMaterial, BulletsWood))
	{
		ResLoadDelegate.ExecuteIfBound(false);
		return;
	}

	TArray<FSoftObjectPath> SandMaterial = FShootingConfigs::GetInstance()->GetBulletDecalWithType(SurfaceType4);
	if (!RequestSyncLoad(SandMaterial, BulletsSand))
	{
		ResLoadDelegate.ExecuteIfBound(false);
		return;
	}

	TArray<FSoftObjectPath> BrickMaterial = FShootingConfigs::GetInstance()->GetBulletDecalWithType(SurfaceType5);
	if (!RequestSyncLoad(BrickMaterial, BulletsBrick))
	{
		ResLoadDelegate.ExecuteIfBound(false);
		return;
	}

	TArray<FSoftObjectPath> GlassMaterial = FShootingConfigs::GetInstance()->GetBulletDecalWithType(SurfaceType6);
	if (!RequestSyncLoad(GlassMaterial, BulletsGlass))
	{
		ResLoadDelegate.ExecuteIfBound(false);
		return;
	}

	TArray<FSoftObjectPath> GroundMaterial = FShootingConfigs::GetInstance()->GetBulletDecalWithType(SurfaceType7);
	if (!RequestSyncLoad(GroundMaterial, BulletsGround))
	{
		ResLoadDelegate.ExecuteIfBound(false);
		return;
	}*/

	FString defaultVF = FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType_Default);
	//FString MetalVF = FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType1);
	//FString WoodVF = FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType2);
	//FString WaterVF = FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType3);
	//FString SandVF = FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType4);
	//FString BrickVF = FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType5);
	//FString GlassVF = FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType6);
	//FString GroundVF = FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType7);
	//FString BloodVF = FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType8);

	if (!RequestSyncLoadOne(FSoftObjectPath(defaultVF), VF_Common))
	{
		ResLoadDelegate.ExecuteIfBound(false);
		return;
	}

	/*if (!RequestSyncLoadOne(FSoftObjectPath(MetalVF), VF_Metal))
	{
		ResLoadDelegate.ExecuteIfBound(false);
		return;
	}

	if (!RequestSyncLoadOne(FSoftObjectPath(WoodVF), VF_Wood))
	{
		ResLoadDelegate.ExecuteIfBound(false);
		return;
	}

	if (!RequestSyncLoadOne(FSoftObjectPath(SandVF), VF_Sand))
	{
		ResLoadDelegate.ExecuteIfBound(false);
		return;
	}

	if (!RequestSyncLoadOne(FSoftObjectPath(BrickVF), VF_Brick))
	{
		ResLoadDelegate.ExecuteIfBound(false);
		return;
	}

	if (!RequestSyncLoadOne(FSoftObjectPath(GlassVF), VF_Glass))
	{
		ResLoadDelegate.ExecuteIfBound(false);
		return;
	}

	if (!RequestSyncLoadOne(FSoftObjectPath(GroundVF), VF_Ground))
	{
		ResLoadDelegate.ExecuteIfBound(false);
		return;
	}

	if (!RequestSyncLoadOne(FSoftObjectPath(WaterVF), VF_Water))
	{
		ResLoadDelegate.ExecuteIfBound(false);
		return;
	}

	if (!RequestSyncLoadOne(FSoftObjectPath(BloodVF), VF_Blood))
	{
		ResLoadDelegate.ExecuteIfBound(false);
		return;
	}*/

	ResLoadDelegate.ExecuteIfBound(true);
}

void FShootingMaterialUtil::RequestAsyncLoad(FString MaterialPath)
{

}

bool FShootingMaterialUtil::RequestSyncLoad(TArray<FSoftObjectPath> ResToLoad, TArray<UObject*>& Resources)
{
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	TSharedPtr<FStreamableHandle> SteamHandle = StreamableManager.RequestSyncLoad(ResToLoad, true);
	if(SteamHandle.IsValid())
	{
		SteamHandle->GetLoadedAssets(Resources);
		return true;
	}

	return false;
}

bool FShootingMaterialUtil::RequestSyncLoadOne(FSoftObjectPath ResToLoad, UObject*& Resource)
{
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	TSharedPtr<FStreamableHandle> SteamHandle = StreamableManager.RequestSyncLoad(ResToLoad, true);
	if (SteamHandle.IsValid())
	{
		Resource = SteamHandle->GetLoadedAsset();
		return true;
	}

	return false;
}


FMaterialLoadDelegate& FShootingMaterialUtil::GetResLoadDelegate()
{
	return ResLoadDelegate;
}

TArray<UObject*> FShootingMaterialUtil::GetBulletsWood()
{
	return BulletsWood;
}

TArray<UObject*> FShootingMaterialUtil::GetBulletsMetal()
{
	return BulletsMetal;
}

TArray<UObject*> FShootingMaterialUtil::GetBulletsCommon()
{
	return BulletsCommon;
}

TArray<UObject*> FShootingMaterialUtil::GetBulletsGlass()
{
	return BulletsGlass;
}

TArray<UObject*> FShootingMaterialUtil::GetBulletsSand()
{
	return BulletsSand;
}

TArray<UObject*> FShootingMaterialUtil::GetBulletsBrick()
{
	return BulletsBrick;
}

TArray<UObject*> FShootingMaterialUtil::GetBulletsGround()
{
	return BulletsGround;
}

TArray<UObject*> FShootingMaterialUtil::GetBulletsWater()
{
	return BulletsWater;
}

UObject* FShootingMaterialUtil::GetVFWood()
{
	return VF_Wood;
}

UObject* FShootingMaterialUtil::GetVFMetal()
{
	return VF_Metal;
}

UObject* FShootingMaterialUtil::GetVFCommon()
{
	return VF_Common;
}

UObject* FShootingMaterialUtil::GetVFGlass()
{
	return VF_Glass;
}

UObject* FShootingMaterialUtil::GetVFSand()
{
	return VF_Sand;
}

UObject* FShootingMaterialUtil::GetVFBrick()
{
	return VF_Brick;
}

UObject* FShootingMaterialUtil::GetVFGround()
{
	return VF_Ground;
}

UObject* FShootingMaterialUtil::GetVFWater()
{
	return VF_Water;
}

UObject* FShootingMaterialUtil::GetVFBlood()
{
	return VF_Blood;
}

