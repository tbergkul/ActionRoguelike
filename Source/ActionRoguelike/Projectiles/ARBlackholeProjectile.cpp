


#include "ARBlackholeProjectile.h"

#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/SphereComponent.h"


AARBlackholeProjectile::AARBlackholeProjectile()
{
	SetLifeSpan(5.0f);

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->Radius = 750.0f;
	RadialForceComponent->ForceStrength = -2000000.0f;
	RadialForceComponent->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	SphereComponent->SetSphereRadius(75.0f);
	SphereComponent->SetCollisionProfileName("Blackhole");
}

void AARBlackholeProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AARBlackholeProjectile::OnActorBeginOverlap);

	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}

void AARBlackholeProjectile::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		if (OtherActor->GetRootComponent()->IsAnySimulatingPhysics())
		{
			OtherActor->Destroy();
		}
	}
}
