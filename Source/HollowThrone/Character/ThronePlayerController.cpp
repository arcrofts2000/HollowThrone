// Copyright - Adam Crofts


#include "ThronePlayerController.h"
#include "../Components/ThroneInteractionComponent.h"
#include "EnhancedInputComponent.h"

AThronePlayerController::AThronePlayerController()
{
	InteractionComponent = CreateDefaultSubobject<UThroneInteractionComponent>(TEXT("InteractionComponent"));
}

void AThronePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInput->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &AThronePlayerController::BeginInteract);
}

void AThronePlayerController::BeginInteract()
{
	InteractionComponent->Interact();
}