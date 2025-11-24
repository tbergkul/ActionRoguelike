


#include "ARBlackholeProjectile.h"

#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AARBlackholeProjectile::AARBlackholeProjectile()
{
	SetLifeSpan(5.0f); // InitialLifeSpan = 5.0f; also works

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->Radius = 750.0f;

	// Negative for attraction
	RadialForceComponent->ForceStrength = -2000000.0f;
	
	// Ignore player and other pawns to prevent weird physics interactions
	RadialForceComponent->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	// Make the blackhole projectile slower
	ProjectileMovementComponent->InitialSpeed = 500.0f;

	// Make the blackhole core a good size and set its collision profile
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
