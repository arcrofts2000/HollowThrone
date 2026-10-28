// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThronePlayerController.generated.h"

class UThroneInteractionComponent;
class UInputAction;

UCLASS()
class HOLLOWTHRONE_API AThronePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AThronePlayerController();

protected:

	// Components
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UThroneInteractionComponent> InteractionComponent;


	// Input

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Interact;


	// Functions

	virtual void SetupInputComponent() override;

	void BeginInteract();
	
};
