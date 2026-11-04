// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "ThroneBTDecorator_LowHealth.generated.h"

/**
 * 
 */
UCLASS()
class HOLLOWTHRONE_API UThroneBTDecorator_LowHealth : public UBTDecorator
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float MinimumHealthPercent = 30.f;

	// Found in BTDecorator_IsAtLocation.cpp - used this as reference for how to implement the CalculateRawConditionValue function
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
