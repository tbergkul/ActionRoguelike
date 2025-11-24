


#include "ARActionSystemComponent.h"



UARActionSystemComponent::UARActionSystemComponent()
{

}

void UARActionSystemComponent::ApplyHealthChange(float InValueChange)
{
	float OldHealth = Attributes.Health;

	float MaxHealth = GetDefault<UARActionSystemComponent>()->Attributes.Health;

	Attributes.Health = FMath::Clamp(Attributes.Health + InValueChange, 0.0f, MaxHealth);

	if (!FMath::IsNearlyEqual(Attributes.Health, OldHealth))
	{
		OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
	}

	UE_LOG(LogTemp, Log, TEXT("New Health: %f, Max Health: %f"), Attributes.Health, MaxHealth);
}

