


#include "ARPlayerController.h"

#include "ARInteractionComponent.h"

AARPlayerController::AARPlayerController()
{
	InteractionComponent = CreateDefaultSubobject<UARInteractionComponent>(TEXT("InteractionComp"));
}
