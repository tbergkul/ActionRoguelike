

#pragma once

#include "ARProjectile.h"
#include "ARTeleportProjectile.generated.h"

class UNiagaraSystem;

UCLASS(Abstract)
class ACTIONROGUELIKE_API AARTeleportProjectile : public AARProjectile
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> TeleportEffect;
	
	UFUNCTION()
	void TeleportAfterDelay();
	
	UFUNCTION()
	void TeleportStart();

	bool bHasStartedTeleport = false;


public:

	AARTeleportProjectile();

	void PostInitializeComponents();

	virtual void BeginPlay() override;

	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	
	
};
