// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingUtil.h"

// ��ȡ���еĲ���
EPhysicalSurface FShootingUtil::GetPhysicalSurfaceType(UPhysicalMaterial* material)
{
	if(material == NULL)
	{
		return EPhysicalSurface::SurfaceType_Default;
	}

	return UPhysicalMaterial::DetermineSurfaceType(material);
}

UMaterialInterface* FShootingUtil::RandomGenerateBulletHole(EPhysicalSurface type)
{
	TArray<UObject*> Objects;

	switch (type)
	{
	case SurfaceType_Default:
		Objects = FShootingMaterialUtil::GetInstance()->GetBulletsCommon();
		break;
	case SurfaceType1:
		Objects = FShootingMaterialUtil::GetInstance()->GetBulletsMetal();
		break;
	case SurfaceType2:
		Objects = FShootingMaterialUtil::GetInstance()->GetBulletsWood();
		break;
	case SurfaceType3:
		break;
	case SurfaceType4:
		Objects = FShootingMaterialUtil::GetInstance()->GetBulletsSand();
		break;
	case SurfaceType5:
		Objects = FShootingMaterialUtil::GetInstance()->GetBulletsBrick();
		break;
	case SurfaceType6:
		Objects = FShootingMaterialUtil::GetInstance()->GetBulletsGlass();
		break;
	case SurfaceType7:
		Objects = FShootingMaterialUtil::GetInstance()->GetBulletsGround();
		break;
	case SurfaceType8:
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

	if(Objects.Num() == 0)
	{
		return NULL;
	}
	
	int32 index = FMath::RandRange(0, Objects.Num() - 1);

	if(!Objects[index])
	{
		return NULL;
	}

	UMaterialInterface* materialIns = Cast<UMaterialInterface>(Objects[index]);
	return materialIns;
}

// ��ȡ��������Ч��
UNiagaraSystem* FShootingUtil::GetImpactParticleSyatem(EPhysicalSurface type)
{
	UNiagaraSystem* Niagara = NULL;
	switch (type)
	{
	case SurfaceType_Default:
		Niagara = Cast<UNiagaraSystem>(FShootingMaterialUtil::GetInstance()->GetVFCommon());
		break;
	case SurfaceType1:
		Niagara = Cast<UNiagaraSystem>(FShootingMaterialUtil::GetInstance()->GetVFMetal());
		break;
	case SurfaceType2:
		Niagara = Cast<UNiagaraSystem>(FShootingMaterialUtil::GetInstance()->GetVFWood());
		break;
	case SurfaceType3:
		Niagara = Cast<UNiagaraSystem>(FShootingMaterialUtil::GetInstance()->GetVFWater());
		break;
	case SurfaceType4:
		Niagara = Cast<UNiagaraSystem>(FShootingMaterialUtil::GetInstance()->GetVFSand());
		break;
	case SurfaceType5:
		Niagara = Cast<UNiagaraSystem>(FShootingMaterialUtil::GetInstance()->GetVFBrick());
		break;
	case SurfaceType6:
		Niagara = Cast<UNiagaraSystem>(FShootingMaterialUtil::GetInstance()->GetVFGlass());
		break;
	case SurfaceType7:
		Niagara = Cast<UNiagaraSystem>(FShootingMaterialUtil::GetInstance()->GetVFGround());
		break;
	case SurfaceType8:
		Niagara = Cast<UNiagaraSystem>(FShootingMaterialUtil::GetInstance()->GetVFBlood());
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

	if(!Niagara)
	{
		return NULL;
	}

	return Niagara;
}




