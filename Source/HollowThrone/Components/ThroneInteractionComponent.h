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

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
