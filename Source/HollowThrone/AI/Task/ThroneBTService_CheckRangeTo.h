// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ThroneBTService_CheckRangeTo.generated.h"

struct FBlackboardKeySelector;

UCLASS()
class HOLLOWTHRONE_API UThroneBTService_CheckRangeTo : public UBTService
{
	GENERATED_BODY()

public:

	UThroneBTService_CheckRangeTo();

	
	UPROPERTY(EditAnywhere, Category = "AI")
	float MaxAttackRange = 500.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector WithinRangeKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};