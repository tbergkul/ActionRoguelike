


#include "ARPlayerController.h"

#include "EnhancedInputComponent.h"
#include "ARInteractionComponent.h"

AARPlayerController::AARPlayerController()
{
	InteractionComponent = CreateDefaultSubobject<UARInteractionComponent>(TEXT("InteractionComp"));
}

void AARPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInput->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &AARPlayerController::StartInteract);
}

void AARPlayerController::StartInteract()
{
	InteractionComponent->Interact();
}