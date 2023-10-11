// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingMaterialUtil.h"


void FShootingMaterialUtil::PreloadMaterials()
{	
	// ͬ通用材质
	CommonMaterial = FShootingConfigs::GetInstance()->GetBulletDecalWithType(SurfaceType_Default);
	if(!RequestAsyncLoad(CommonMaterial, FStreamableDelegate::CreateRaw(this, &FShootingMaterialUtil::CommonMaterialDeferred)))
	{
		UE_LOG(LogTemp, Error, TEXT("Load SurfaceType_Default Error"));
		return;
	}

	MetalMaterial = FShootingConfigs::GetInstance()->GetBulletDecalWithType(SurfaceType1);
	if(!RequestAsyncLoad(MetalMaterial, FStreamableDelegate::CreateRaw(this, &FShootingMaterialUtil::MetalMaterialDeferred)))
	{
		UE_LOG(LogTemp, Error, TEXT("Load SurfaceType1 Error"));
		return;
	}

	WoodMaterial = FShootingConfigs::GetInstance()->GetBulletDecalWithType(SurfaceType2);
	if (!RequestAsyncLoad(WoodMaterial, FStreamableDelegate::CreateRaw(this, &FShootingMaterialUtil::WoodMaterialDeferred)))
	{
		UE_LOG(LogTemp, Error, TEXT("Load SurfaceType2 Error"));
		return;
	}

	//WaterMaterial = FShootingConfigs::GetInstance()->GetBulletDecalWithType(SurfaceType3);
	//if (!RequestAsyncLoad(WaterMaterial, FStreamableDelegate::CreateRaw(this, &FShootingMaterialUtil::WaterMaterialDeferred)))
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Load SurfaceType3 Error"));
	//	return;
	//}

	SandMaterial = FShootingConfigs::GetInstance()->GetBulletDecalWithType(SurfaceType4);
	if (!RequestAsyncLoad(SandMaterial, FStreamableDelegate::CreateRaw(this, &FShootingMaterialUtil::SandMaterialDeferred)))
	{
		UE_LOG(LogTemp, Error, TEXT("Load SurfaceType4 Error"));
		return;
	}
	
	BrickMaterial = FShootingConfigs::GetInstance()->GetBulletDecalWithType(SurfaceType5);
	if (!RequestAsyncLoad(BrickMaterial, FStreamableDelegate::CreateRaw(this, &FShootingMaterialUtil::BrickMaterialDeferred)))
	{
		UE_LOG(LogTemp, Error, TEXT("Load SurfaceType5 Error"));
		return;
	}

	GlassMaterial = FShootingConfigs::GetInstance()->GetBulletDecalWithType(SurfaceType6);
	if (!RequestAsyncLoad(GlassMaterial, FStreamableDelegate::CreateRaw(this, &FShootingMaterialUtil::GlassMaterialDeferred)))
	{
		UE_LOG(LogTemp, Error, TEXT("Load SurfaceType6 Error"));
		return;
	}

	GroundMaterial = FShootingConfigs::GetInstance()->GetBulletDecalWithType(SurfaceType7);
	if (!RequestAsyncLoad(GroundMaterial, FStreamableDelegate::CreateRaw(this, &FShootingMaterialUtil::GroundMaterialDeferred)))
	{
		UE_LOG(LogTemp, Error, TEXT("Load SurfaceType7 Error"));
		return;
	}

	defaultVF = FSoftObjectPath(FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType_Default));
	if(!RequestAsyncLoadSingle(defaultVF, FStreamableDelegate::CreateRaw(this, &FShootingMaterialUtil::defaultVFDeferred)))
	{
		UE_LOG(LogTemp, Error, TEXT("Load defaultVF Error"));
		return;
	}

	MetalVF = FSoftObjectPath(FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType1));
	if(!RequestAsyncLoadSingle(MetalVF, FStreamableDelegate::CreateRaw(this, &FShootingMaterialUtil::MetalVFDeferred)))
	{
		UE_LOG(LogTemp, Error, TEXT("Load MetalVF Error"));
		return;
	}

	WoodVF = FSoftObjectPath(FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType2));
	if(!RequestAsyncLoadSingle(WoodVF, FStreamableDelegate::CreateRaw(this, &FShootingMaterialUtil::WoodVFDeferred)))
	{
		UE_LOG(LogTemp, Error, TEXT("Load WoodVF Error"));
		return;
	}

	WaterVF = FSoftObjectPath(FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType3));
	if(!RequestAsyncLoadSingle(WaterVF, FStreamableDelegate::CreateRaw(this, &FShootingMaterialUtil::WaterVFDeferred)))
	{
		UE_LOG(LogTemp, Error, TEXT("Load WaterVF Error"));
		return;
	}

	SandVF = FSoftObjectPath(FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType4));
	if(!RequestAsyncLoadSingle(SandVF, FStreamableDelegate::CreateRaw(this, &FShootingMaterialUtil::SandVFDeferred)))
	{
		UE_LOG(LogTemp, Error, TEXT("Load SandVF Error"));
		return;
	}

	BrickVF = FSoftObjectPath(FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType5));
	if(!RequestAsyncLoadSingle(BrickVF, FStreamableDelegate::CreateRaw(this, &FShootingMaterialUtil::BrickVFDeferred)))
	{
		UE_LOG(LogTemp, Error, TEXT("Load BrickVF Error"));
		return;
	}

	GlassVF = FSoftObjectPath(FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType6));
	if(!RequestAsyncLoadSingle(GlassVF, FStreamableDelegate::CreateRaw(this, &FShootingMaterialUtil::GlassVFDeferred)))
	{
		UE_LOG(LogTemp, Error, TEXT("Load GlassVF Error"));
		return;
	}

	GroundVF = FSoftObjectPath(FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType7));
	if(!RequestAsyncLoadSingle(GroundVF, FStreamableDelegate::CreateRaw(this, &FShootingMaterialUtil::GroundVFDeferred)))
	{
		UE_LOG(LogTemp, Error, TEXT("Load GroundVF Error"));
		return;
	}

	BloodVF = FSoftObjectPath(FShootingConfigs::GetInstance()->GetParticleSystemWithType(SurfaceType8));
	if(!RequestAsyncLoadSingle(BloodVF, FStreamableDelegate::CreateRaw(this, &FShootingMaterialUtil::BloodVFDeferred)))
	{
		UE_LOG(LogTemp, Error, TEXT("Load BloodVF Error"));
		return;
	}
}

bool FShootingMaterialUtil::RequestAsyncLoad(TArray<FSoftObjectPath> ResToLoad, FStreamableDelegate DelegateToCall)
{
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	TSharedPtr<FStreamableHandle> SteamHandle = Streamable.RequestAsyncLoad(ResToLoad, DelegateToCall);
	if (!SteamHandle.IsValid())
	{	
		return false;
	}
	return true;
}
 
bool FShootingMaterialUtil::RequestAsyncLoadSingle(FSoftObjectPath ResToLoad, FStreamableDelegate DelegateToCall)
{
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	TSharedPtr<FStreamableHandle> SteamHandle = Streamable.RequestAsyncLoad(ResToLoad, DelegateToCall);
	if (!SteamHandle.IsValid())
	{
		return false;
	}
	return true;
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


void FShootingMaterialUtil::CheckGameResLoad()
{
	if (BulletsCommon.Num() != CommonMaterial.Num())
	{
		return;
	}

	if (BulletsMetal.Num() != MetalMaterial.Num())
	{
		return;
	}

	if (BulletsWood.Num() != WoodMaterial.Num())
	{
		
		return;
	}

	//if (BulletsWater.Num() != WaterMaterial.Num())
	//{
	//	
	//	return;
	//}

	if (BulletsSand.Num() != SandMaterial.Num())
	{
		
		return;
	}

	if (BulletsBrick.Num() != BrickMaterial.Num())
	{
		
		return;
	}

	if(BulletsGlass.Num() != GlassMaterial.Num())
	{
		return;
	}

	if (BulletsGround.Num() != GroundMaterial.Num())
	{
		
		return;
	}

	if(!VF_Default || !VF_Ground || !VF_Wood || !VF_Glass || !VF_Metal || !VF_Water || !VF_Sand || !VF_Brick || !VF_Blood)
	{
		UE_LOG(LogTemp, Log, TEXT("VF Res Load not ready"));
		return;
	}
	
	UE_LOG(LogTemp, Log, TEXT("Res Load complete"));
	ResLoadDelegate.ExecuteIfBound(true);
}

//=========================================CALL BACK=============================================
void FShootingMaterialUtil::CommonMaterialDeferred()
{
	for (FSoftObjectPath SoftObj : CommonMaterial)
	{
		TAssetPtr<UObject> p_Obj(SoftObj);
		UObject* Obj = p_Obj.Get();
		if (Obj)
		{
			BulletsCommon.Add(Obj);
		}
	}
}

void FShootingMaterialUtil::MetalMaterialDeferred()
{
	for (FSoftObjectPath SoftObj : MetalMaterial)
	{
		TAssetPtr<UObject> p_Obj(SoftObj);
		UObject* Obj = p_Obj.Get();
		if (Obj)
		{
			BulletsMetal.Add(Obj);
		}
	}

	CheckGameResLoad();
}

void FShootingMaterialUtil::WoodMaterialDeferred()
{
	for (FSoftObjectPath SoftObj : WoodMaterial)
	{
		TAssetPtr<UObject> p_Obj(SoftObj);
		UObject* Obj = p_Obj.Get();
		if (Obj)
		{
			BulletsWood.Add(Obj);
		}
	}

	CheckGameResLoad();
}

void FShootingMaterialUtil::WaterMaterialDeferred()
{
	for (FSoftObjectPath SoftObj : WaterMaterial)
	{
		TAssetPtr<UObject> p_Obj(SoftObj);
		UObject* Obj = p_Obj.Get();
		if (Obj)
		{
			BulletsWater.Add(Obj);
		}
	}

	CheckGameResLoad();
}

void FShootingMaterialUtil::SandMaterialDeferred()
{
	for (FSoftObjectPath SoftObj : SandMaterial)
	{
		TAssetPtr<UObject> p_Obj(SoftObj);
		UObject* Obj = p_Obj.Get();
		if (Obj)
		{
			BulletsSand.Add(Obj);
		}
	}

	CheckGameResLoad();
}

void FShootingMaterialUtil::BrickMaterialDeferred()
{
	for (FSoftObjectPath SoftObj : BrickMaterial)
	{
		TAssetPtr<UObject> p_Obj(SoftObj);
		UObject* Obj = p_Obj.Get();
		if (Obj)
		{
			BulletsBrick.Add(Obj);
		}
	}

	CheckGameResLoad();
}

void FShootingMaterialUtil::GlassMaterialDeferred()
{
	for (FSoftObjectPath SoftObj : GlassMaterial)
	{
		TAssetPtr<UObject> p_Obj(SoftObj);
		UObject* Obj = p_Obj.Get();
		if (Obj)
		{
			BulletsGlass.Add(Obj);
		}
	}

	CheckGameResLoad();
}

void FShootingMaterialUtil::GroundMaterialDeferred()
{
	for (FSoftObjectPath SoftObj : GroundMaterial)
	{
		TAssetPtr<UObject> p_Obj(SoftObj);
		UObject* Obj = p_Obj.Get();
		if (Obj)
		{
			BulletsGround.Add(Obj);
		}
	}

	CheckGameResLoad();
}

void FShootingMaterialUtil::defaultVFDeferred()
{
	TAssetPtr<UObject> p_Obj(defaultVF);
	UObject* Obj = p_Obj.Get();
	if (Obj)
	{
		VF_Default = Obj;
	}

	CheckGameResLoad();
}

void FShootingMaterialUtil::MetalVFDeferred()
{
	TAssetPtr<UObject> p_Obj(MetalVF);
	UObject* Obj = p_Obj.Get();
	if (Obj)
	{
		VF_Metal = Obj;
	}

	CheckGameResLoad();
}

void FShootingMaterialUtil::WoodVFDeferred()
{
	TAssetPtr<UObject> p_Obj(WoodVF);
	UObject* Obj = p_Obj.Get();
	if (Obj)
	{
		VF_Wood = Obj;
	}

	CheckGameResLoad();
}

void FShootingMaterialUtil::WaterVFDeferred()
{
	TAssetPtr<UObject> p_Obj(WaterVF);
	UObject* Obj = p_Obj.Get();
	if (Obj)
	{
		VF_Water = Obj;
	}

	CheckGameResLoad();
}

void FShootingMaterialUtil::SandVFDeferred()
{
	TAssetPtr<UObject> p_Obj(SandVF);
	UObject* Obj = p_Obj.Get();
	if (Obj)
	{
		VF_Sand = Obj;
	}

	CheckGameResLoad();
}

void FShootingMaterialUtil::BrickVFDeferred()
{
	TAssetPtr<UObject> p_Obj(BrickVF);
	UObject* Obj = p_Obj.Get();
	if (Obj)
	{
		VF_Brick = Obj;
	}

	CheckGameResLoad();
}

void FShootingMaterialUtil::GlassVFDeferred()
{
	TAssetPtr<UObject> p_Obj(GlassVF);
	UObject* Obj = p_Obj.Get();
	if (Obj)
	{
		VF_Glass = Obj;
	}

	CheckGameResLoad();
}

void FShootingMaterialUtil::GroundVFDeferred()
{
	TAssetPtr<UObject> p_Obj(GroundVF);
	UObject* Obj = p_Obj.Get();
	if (Obj)
	{
		VF_Ground = Obj;
	}

	CheckGameResLoad();
}

void FShootingMaterialUtil::BloodVFDeferred()
{
	TAssetPtr<UObject> p_Obj(BloodVF);
	UObject* Obj = p_Obj.Get();
	if (Obj)
	{
		VF_Blood = Obj;
	}

	CheckGameResLoad();
}
