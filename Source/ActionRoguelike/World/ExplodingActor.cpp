// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodingActor.h"

#include "Components/StaticMeshComponent.h"
#include <Kismet/GameplayStatics.h>
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AExplodingActor::AExplodingActor()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionProfileName("PhysicsActor");

	LoopedFuseNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopedFuseNiagaraComp"));
	LoopedFuseNiagaraComponent->SetupAttachment(StaticMeshComponent);
	LoopedFuseNiagaraComponent->bAutoActivate = false;

	LoopedFuseAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopedFuseAudioComp"));
	LoopedFuseAudioComponent->SetupAttachment(StaticMeshComponent);
	LoopedFuseAudioComponent->bAutoActivate = false;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComponent->ImpulseStrength = 80000;
	RadialForceComponent->Radius = 1500;
}

float AExplodingActor::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	LoopedFuseNiagaraComponent->ActivateSystem();

	LoopedFuseAudioComponent->Activate();

	FTimerHandle FuseTimerHandle;
	const float FuseDelayTime = 3.0f;

	GetWorldTimerManager().SetTimer(FuseTimerHandle, this, &AExplodingActor::Explode, FuseDelayTime);

	return (DamageAmount);
}

void AExplodingActor::Explode()
{
	RadialForceComponent->FireImpulse();

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());

	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation(), FRotator::ZeroRotator);
	
	Destroy();
}
