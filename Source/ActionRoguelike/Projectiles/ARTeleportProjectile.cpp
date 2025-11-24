


#include "ARTeleportProjectile.h"

#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"

AARTeleportProjectile::AARTeleportProjectile()
{
	ProjectileMovementComponent->InitialSpeed = 6000.f;
}

void AARTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle SelfTeleportTimerHandle;
	const float SelfTeleportDelay = 0.2f;
	GetWorldTimerManager().SetTimer(SelfTeleportTimerHandle, this, &AARTeleportProjectile::TeleportStart, SelfTeleportDelay);
}

void AARTeleportProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	TeleportStart();
}

void AARTeleportProjectile::TeleportStart()
{
	if (bHasStartedTeleport)
	{
		return;
	}
	bHasStartedTeleport = true;

	if (IsValid(TeleportEffect))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TeleportEffect, GetActorLocation(), GetActorRotation());
	}

	ProjectileMovementComponent->StopMovementImmediately();

	FTimerHandle TeleportDelayTimerHandle;
	const float TeleportDelay = 0.2f;
	FTimerDelegate TeleportDelayDelegate;
	TeleportDelayDelegate.BindUFunction(this, FName("TeleportAfterDelay"));
	GetWorldTimerManager().SetTimer(TeleportDelayTimerHandle, TeleportDelayDelegate, TeleportDelay, false);
}

void AARTeleportProjectile::TeleportAfterDelay()
{
	GetInstigator()->TeleportTo(GetActorLocation(), GetInstigator()->GetActorRotation());
	Destroy();
}

