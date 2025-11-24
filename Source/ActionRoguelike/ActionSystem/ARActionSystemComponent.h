

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ARActionSystemComponent.generated.h"


USTRUCT(BlueprintType)
struct FARAttributeSet
{
	GENERATED_BODY()

	FARAttributeSet()
		: Health(100.0f) {}

	UPROPERTY(BlueprintReadOnly)
	float Health;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API UARActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

	
public:

	void ApplyHealthChange(float InValueChange);

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;


protected:

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FARAttributeSet Attributes;

public:	

	UARActionSystemComponent();
		
	
};
