// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ThroneAIController.generated.h"

class UBehaviorTree;

UCLASS()
class HOLLOWTHRONE_API AThroneAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	AThroneAIController();


protected:

	// Assets

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> AIBehaviourTree;


	// Functions

	virtual void BeginPlay() override;
};
