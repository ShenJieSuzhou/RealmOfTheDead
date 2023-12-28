// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "BulletImpactEffect.generated.h"

UCLASS()
class ROTD_API ABulletImpactEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletImpactEffect();

	UPROPERTY(VisibleDefaultsOnly, Category = "Niagara")
	UNiagaraComponent* Niagara;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetNiagaraSysAsset(UNiagaraSystem* NiagaraAsset);

};
