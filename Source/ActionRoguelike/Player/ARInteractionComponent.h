

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ARInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API UARInteractionComponent : public UActorComponent
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionRadius = 500.0f;

	UPROPERTY()
	TObjectPtr<AActor> SelectedActor;


public:	

	void Interact();
	
	UARInteractionComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
