// Copyright - Adam Crofts


#include "AI/Decorator/ThroneBTDecorator_LowHealth.h"
#include "AIController.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"

bool UThroneBTDecorator_LowHealth::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	APawn* OwnedPawn = Controller->GetPawn();
	check(OwnedPawn);

	// ASC should be valid. ensureMsgf done to log an error in case a user attempts to call this Decorator without an AbilitySystemComponent on the Pawn.
	UThroneAbilitySystemComponent* ASC = OwnedPawn->GetComponentByClass<UThroneAbilitySystemComponent>();
	ensureMsgf(ASC, TEXT("UThroneBTDecorator_LowHealth: Pawn is missing AbilitySystemComponent"));

	// If the Health Percentage is less than the minimum health percent, return true.
	return ASC->GetHealthPercent() <= MinimumHealthPercent ? true : false;
}
