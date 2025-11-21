

#pragma once

#include "ARProjectile.h"
#include "ARBlackholeProjectile.generated.h"

class URadialForceComponent;

UCLASS(Abstract)
class ACTIONROGUELIKE_API AARBlackholeProjectile : public AARProjectile
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;

	UFUNCTION()
	void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	

	AARBlackholeProjectile();

	void PostInitializeComponents();

	
};
