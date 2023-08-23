// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletImpactEffect.h"

// Sets default values
ABulletImpactEffect::ABulletImpactEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	Niagara->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABulletImpactEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletImpactEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletImpactEffect::SetNiagaraSysAsset(UNiagaraSystem* NiagaraAsset)
{
	if(NiagaraAsset)
	{
		Niagara->SetAsset(NiagaraAsset);
	}
}

