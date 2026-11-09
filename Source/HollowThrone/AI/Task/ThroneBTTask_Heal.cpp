// Copyright - Adam Crofts


#include "AI/Task/ThroneBTTask_Heal.h"
#include "AIController.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ThroneGameplayTags.h"

EBTNodeResult::Type UThroneBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// APawn should be valid, check done anyway.
	AAIController* Controller = OwnerComp.GetAIOwner();
	APawn* OwnedPawn = Controller->GetPawn();
	check(OwnedPawn);

	// Made ensureMsgf as AI should have this in order to heal, but used Msgf to provide context to users in case of failure.
	UThroneAbilitySystemComponent* ASC = OwnedPawn->GetComponentByClass<UThroneAbilitySystemComponent>();
	ensureMsgf(ASC, TEXT("UThroneBTTask_Heal::ExecuteTask - Pawn %s does not have a UThroneAbilitySystemComponent, cannot heal."), *OwnedPawn->GetName());

	if (ASC->ApplyAttributeChange(ThroneGameplayTags::Attribute_Health, HealAmount, EAttributeModifyType::Base))
	{
		// If the heal was successful, play the sound and return success.
		UGameplayStatics::PlaySoundAtLocation(this, HealSound, OwnedPawn->GetActorLocation());
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
