// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingConfigs.h"

TArray<FSoftObjectPath> FShootingConfigs::GetBulletDecalWithType(EPhysicalSurface type)
{
	switch (type)
	{
	case SurfaceType_Default:
	{
		// 通用
		TArray<FSoftObjectPath> StringArray;
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Generic/MI_Generic_1.MI_Generic_1'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Generic/MI_Generic_2.MI_Generic_2'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Generic/MI_Generic_3.MI_Generic_3'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Generic/MI_Generic_4.MI_Generic_4'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Generic/MI_Generic_5.MI_Generic_5'")));
		return StringArray;
	}
		break;
	case SurfaceType1:
	{
		// 金属
		TArray<FSoftObjectPath> StringArray;
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Metal_Solid/MI_Metal_Solid_1.MI_Metal_Solid_1'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Metal_Solid/MI_Metal_Solid_2.MI_Metal_Solid_2'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Metal_Solid/MI_Metal_Solid_3.MI_Metal_Solid_3'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Metal_Solid/MI_Metal_Solid_4.MI_Metal_Solid_4'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Metal_Solid/MI_Metal_Solid_5.MI_Metal_Solid_5'")));
		return StringArray;
	}
		break;
	case SurfaceType2:
	{
		// 木头
		TArray<FSoftObjectPath> StringArray;
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Wood/MI_Wood_1.MI_Wood_1'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Wood/MI_Wood_2.MI_Wood_2'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Wood/MI_Wood_3.MI_Wood_3'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Wood/MI_Wood_4.MI_Wood_4'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Wood/MI_Wood_5.MI_Wood_5'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Wood/MI_Wood_6.MI_Wood_6'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Wood/MI_Wood_7.MI_Wood_7'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Wood/MI_Wood_8.MI_Wood_8'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Wood/MI_Wood_9.MI_Wood_9'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Wood/MI_Wood_10.MI_Wood_10'")));
		return StringArray;
	}
		break;
	case SurfaceType3:
		// 水
		break;
	case SurfaceType4:
	{
		// 沙地
		TArray<FSoftObjectPath> StringArray;
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Sand/MI_Sand_1.MI_Sand_1'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Sand/MI_Sand_2.MI_Sand_2'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Sand/MI_Sand_3.MI_Sand_3'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Sand/MI_Sand_4.MI_Sand_4'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Sand/MI_Sand_5.MI_Sand_5'")));
		return StringArray;
	}
		break;
	case SurfaceType5:
	{
		// 砖头
		TArray<FSoftObjectPath> StringArray;
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Rock/MI_Rock_1.MI_Rock_1'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Rock/MI_Rock_2.MI_Rock_2'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Rock/MI_Rock_3.MI_Rock_3'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Rock/MI_Rock_4.MI_Rock_4'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Rock/MI_Rock_5.MI_Rock_5'")));
		return StringArray;
	}
		break;
	case SurfaceType6:
	{
		// 玻璃
		TArray<FSoftObjectPath> StringArray;
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Glass_Common_Mesh_Decals/MI_Glass_Common_1.MI_Glass_Common_1'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Glass_Common_Mesh_Decals/MI_Glass_Common_2.MI_Glass_Common_2'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Glass_Common_Mesh_Decals/MI_Glass_Common_3.MI_Glass_Common_3'")));
		return StringArray;
	}
		break;
	case SurfaceType7:
	{
		// 草地
		TArray<FSoftObjectPath> StringArray = {
			FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Ground/MI_Ground_1.MI_Ground_1'")),
			FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Ground/MI_Ground_2.MI_Ground_2'")),
			FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Ground/MI_Ground_3.MI_Ground_3'")),
			FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Ground/MI_Ground_4.MI_Ground_4'")),
			FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Ground/MI_Ground_5.MI_Ground_5'"))
		};
		return StringArray;
	}
		break;
	case SurfaceType8:
	{
		TArray<FSoftObjectPath> StringArray;
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Flesh/MI_Flesh_1.MI_Flesh_1'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Flesh/MI_Flesh_2.MI_Flesh_2'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Flesh/MI_Flesh_3.MI_Flesh_3'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Flesh/MI_Flesh_4.MI_Flesh_4'")));
		StringArray.Add(FSoftObjectPath(TEXT("MaterialInstanceConstant'/Game/UWC_Bullet_Holes/Instances/Decals/Flesh/MI_Flesh_5.MI_Flesh_5'")));
		return StringArray;
	}
		// 皮肤
		break;
	case SurfaceType9:
		break;
	case SurfaceType10:
		break;
	case SurfaceType11:
		break;
	case SurfaceType12:
		break;
	case SurfaceType13:
		break;
	case SurfaceType14:
		break;
	case SurfaceType15:
		break;
	case SurfaceType16:
		break;
	case SurfaceType17:
		break;
	case SurfaceType18:
		break;
	case SurfaceType19:
		break;
	case SurfaceType20:
		break;
	case SurfaceType21:
		break;
	case SurfaceType22:
		break;
	case SurfaceType23:
		break;
	case SurfaceType24:
		break;
	case SurfaceType25:
		break;
	case SurfaceType26:
		break;
	case SurfaceType27:
		break;
	case SurfaceType28:
		break;
	case SurfaceType29:
		break;
	case SurfaceType30:
		break;
	case SurfaceType31:
		break;
	case SurfaceType32:
		break;
	case SurfaceType33:
		break;
	case SurfaceType34:
		break;
	case SurfaceType35:
		break;
	case SurfaceType36:
		break;
	case SurfaceType37:
		break;
	case SurfaceType38:
		break;
	case SurfaceType39:
		break;
	case SurfaceType40:
		break;
	case SurfaceType41:
		break;
	case SurfaceType42:
		break;
	case SurfaceType43:
		break;
	case SurfaceType44:
		break;
	case SurfaceType45:
		break;
	case SurfaceType46:
		break;
	case SurfaceType47:
		break;
	case SurfaceType48:
		break;
	case SurfaceType49:
		break;
	case SurfaceType50:
		break;
	case SurfaceType51:
		break;
	case SurfaceType52:
		break;
	case SurfaceType53:
		break;
	case SurfaceType54:
		break;
	case SurfaceType55:
		break;
	case SurfaceType56:
		break;
	case SurfaceType57:
		break;
	case SurfaceType58:
		break;
	case SurfaceType59:
		break;
	case SurfaceType60:
		break;
	case SurfaceType61:
		break;
	case SurfaceType62:
		break;
	case SurfaceType_Max:
		break;
	default:
		break;
	}

    return TArray<FSoftObjectPath>();
}

FString FShootingConfigs::GetParticleSystemWithType(EPhysicalSurface type)
{
	switch (type)
	{
	case SurfaceType_Default:
		return TEXT("NiagaraSystem'/Game/Realistic_Starter_VFX_Pack_Niagara/Niagara/Impact/NS_Impact_Default.NS_Impact_Default'");
		break;
	case SurfaceType1:
		// 金属
		return TEXT("NiagaraSystem'/Game/Realistic_Starter_VFX_Pack_Niagara/Niagara/Impact/NS_Impact_Metal.NS_Impact_Metal'");
		break;
	case SurfaceType2:
		// 木头
		return TEXT("NiagaraSystem'/Game/Realistic_Starter_VFX_Pack_Niagara/Niagara/Impact/NS_Impact_Wood.NS_Impact_Wood'");
		break;
	case SurfaceType3:
		// 水
		return TEXT("NiagaraSystem'/Game/Realistic_Starter_VFX_Pack_Niagara/Niagara/Impact/NS_Impact_Water.NS_Impact_Water'");
		break;
	case SurfaceType4:
		// 沙子
		return TEXT("NiagaraSystem'/Game/Realistic_Starter_VFX_Pack_Niagara/Niagara/Impact/NS_Impact_Sand.NS_Impact_Sand'");
		break;
	case SurfaceType5:
		// 砖头
		return TEXT("NiagaraSystem'/Game/Realistic_Starter_VFX_Pack_Niagara/Niagara/Impact/NS_Impact_Brick.NS_Impact_Brick'");
		break;
	case SurfaceType6:
		// 玻璃
		return TEXT("NiagaraSystem'/Game/Realistic_Starter_VFX_Pack_Niagara/Niagara/Impact/NS_Impact_Glass.NS_Impact_Glass'");
		break;
	case SurfaceType7:
		// 植物
		return TEXT("NiagaraSystem'/Game/Realistic_Starter_VFX_Pack_Niagara/Niagara/Impact/NS_Impact_Grass.NS_Impact_Grass'");
		break;
	case SurfaceType8:
		// 皮肤
		return TEXT("NiagaraSystem'/Game/Realistic_Starter_VFX_Pack_Niagara/Niagara/Impact/NS_Impact_Blood.NS_Impact_Blood'");
		break;
	case SurfaceType9:
		break;
	case SurfaceType10:
		break;
	case SurfaceType11:
		break;
	case SurfaceType12:
		break;
	case SurfaceType13:
		break;
	case SurfaceType14:
		break;
	case SurfaceType15:
		break;
	case SurfaceType16:
		break;
	case SurfaceType17:
		break;
	case SurfaceType18:
		break;
	case SurfaceType19:
		break;
	case SurfaceType20:
		break;
	case SurfaceType21:
		break;
	case SurfaceType22:
		break;
	case SurfaceType23:
		break;
	case SurfaceType24:
		break;
	case SurfaceType25:
		break;
	case SurfaceType26:
		break;
	case SurfaceType27:
		break;
	case SurfaceType28:
		break;
	case SurfaceType29:
		break;
	case SurfaceType30:
		break;
	case SurfaceType31:
		break;
	case SurfaceType32:
		break;
	case SurfaceType33:
		break;
	case SurfaceType34:
		break;
	case SurfaceType35:
		break;
	case SurfaceType36:
		break;
	case SurfaceType37:
		break;
	case SurfaceType38:
		break;
	case SurfaceType39:
		break;
	case SurfaceType40:
		break;
	case SurfaceType41:
		break;
	case SurfaceType42:
		break;
	case SurfaceType43:
		break;
	case SurfaceType44:
		break;
	case SurfaceType45:
		break;
	case SurfaceType46:
		break;
	case SurfaceType47:
		break;
	case SurfaceType48:
		break;
	case SurfaceType49:
		break;
	case SurfaceType50:
		break;
	case SurfaceType51:
		break;
	case SurfaceType52:
		break;
	case SurfaceType53:
		break;
	case SurfaceType54:
		break;
	case SurfaceType55:
		break;
	case SurfaceType56:
		break;
	case SurfaceType57:
		break;
	case SurfaceType58:
		break;
	case SurfaceType59:
		break;
	case SurfaceType60:
		break;
	case SurfaceType61:
		break;
	case SurfaceType62:
		break;
	case SurfaceType_Max:
		break;
	default:
		break;
	}

    return FString();
}

FString FShootingConfigs::GetBPClassPathWithType(EPhysicalSurface type)
{
	switch (type)
	{
	case SurfaceType_Default:
		return TEXT("Blueprint'/Game/ShootingPawn/Blueprints/BulletHoles/Common_BP.Common_BP_C'");
		break;
	case SurfaceType1:
		// 金属
		return TEXT("Blueprint'/Game/ShootingPawn/Blueprints/BulletHoles/Metal_BP.Metal_BP_C'");
		break;
	case SurfaceType2:
		// 木头
		return TEXT("Blueprint'/Game/ShootingPawn/Blueprints/BulletHoles/Wood_BP.Wood_BP_C'");
		break;
	case SurfaceType3:
		// 水
		return TEXT("");
		break;
	case SurfaceType4:
		// 沙子
		return TEXT("");
		break;
	case SurfaceType5:
		// 砖头
		return TEXT("");
		break;
	case SurfaceType6:
		// 玻璃
		return TEXT("");
		break;
	case SurfaceType7:
		// 植物
		return TEXT("Blueprint'/Game/ShootingPawn/Blueprints/BulletHoles/Glass_BP.Glass_BP_C'");
		break;
	case SurfaceType8:
		// 皮肤
		return TEXT("");
		break;
	case SurfaceType9:
		break;
	case SurfaceType10:
		break;
	case SurfaceType11:
		break;
	case SurfaceType12:
		break;
	case SurfaceType13:
		break;
	case SurfaceType14:
		break;
	case SurfaceType15:
		break;
	case SurfaceType16:
		break;
	case SurfaceType17:
		break;
	case SurfaceType18:
		break;
	case SurfaceType19:
		break;
	case SurfaceType20:
		break;
	case SurfaceType21:
		break;
	case SurfaceType22:
		break;
	case SurfaceType23:
		break;
	case SurfaceType24:
		break;
	case SurfaceType25:
		break;
	case SurfaceType26:
		break;
	case SurfaceType27:
		break;
	case SurfaceType28:
		break;
	case SurfaceType29:
		break;
	case SurfaceType30:
		break;
	case SurfaceType31:
		break;
	case SurfaceType32:
		break;
	case SurfaceType33:
		break;
	case SurfaceType34:
		break;
	case SurfaceType35:
		break;
	case SurfaceType36:
		break;
	case SurfaceType37:
		break;
	case SurfaceType38:
		break;
	case SurfaceType39:
		break;
	case SurfaceType40:
		break;
	case SurfaceType41:
		break;
	case SurfaceType42:
		break;
	case SurfaceType43:
		break;
	case SurfaceType44:
		break;
	case SurfaceType45:
		break;
	case SurfaceType46:
		break;
	case SurfaceType47:
		break;
	case SurfaceType48:
		break;
	case SurfaceType49:
		break;
	case SurfaceType50:
		break;
	case SurfaceType51:
		break;
	case SurfaceType52:
		break;
	case SurfaceType53:
		break;
	case SurfaceType54:
		break;
	case SurfaceType55:
		break;
	case SurfaceType56:
		break;
	case SurfaceType57:
		break;
	case SurfaceType58:
		break;
	case SurfaceType59:
		break;
	case SurfaceType60:
		break;
	case SurfaceType61:
		break;
	case SurfaceType62:
		break;
	case SurfaceType_Max:
		break;
	default:
		break;
	}

	return FString();
}
