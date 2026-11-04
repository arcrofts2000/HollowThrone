// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ThroneBTTask_Heal.generated.h"

class USoundBase;

UCLASS()
class HOLLOWTHRONE_API UThroneBTTask_Heal : public UBTTaskNode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<USoundBase> HealSound;

	UPROPERTY(EditAnywhere, Category = "AI")
	float HealAmount = 20.f;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
