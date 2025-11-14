// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplodingActor.generated.h"

class UStaticMeshComponent;
class UNiagaraSystem;
class UAudioComponent;
class UNiagaraComponent;
class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API AExplodingActor : public AActor
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UNiagaraComponent> LoopedFuseNiagaraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundBase> ExplosionSound;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UAudioComponent> LoopedFuseAudioComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;


public:	

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	void Explode();

	AExplodingActor();

};
