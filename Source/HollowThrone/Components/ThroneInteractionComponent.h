// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThroneInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOLLOWTHRONE_API UThroneInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UThroneInteractionComponent();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InteractionRadius;

	UPROPERTY()
	TObjectPtr<AActor> ClosestActor;


public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Interact();

		
};
