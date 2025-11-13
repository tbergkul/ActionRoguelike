

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ARPlayerController.generated.h"

class UInputAction;
class UARInteractionComponent;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API AARPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
protected:

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Interact;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UARInteractionComponent> InteractionComponent;


	void StartInteract();

	virtual void SetupInputComponent() override;

public:

	AARPlayerController();
	
};
