// Copyright - Adam Crofts


#include "ThronePlayerController.h"
#include "../Components/ThroneInteractionComponent.h"

AThronePlayerController::AThronePlayerController()
{
	InteractionComponent = CreateDefaultSubobject<UThroneInteractionComponent>(TEXT("InteractionComponent"));
}