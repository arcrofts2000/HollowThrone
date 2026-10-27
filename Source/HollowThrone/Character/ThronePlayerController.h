// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThronePlayerController.generated.h"

class UThroneInteractionComponent;

UCLASS()
class HOLLOWTHRONE_API AThronePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AThronePlayerController();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UThroneInteractionComponent> InteractionComponent;
	
};
