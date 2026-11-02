// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ThroneBTTask_RangedAttack.generated.h"

class AThroneProjectileBase;

UCLASS()
class HOLLOWTHRONE_API UThroneBTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AThroneProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "AI")
	FName MuzzleSocketName;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	float BulletSpread = 2.f;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
