// Copyright - Adam Crofts


#include "AI/QueryContext/ThroneEQContext_TargetActor.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ThroneGameTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"



void UThroneEQContext_TargetActor::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	APawn* QuerierPawn = Cast<APawn>(QueryInstance.Owner.Get());

	// QuerierPawn could be misconfigured by user (designer, for example) in EQS. TODO: Impl. Log warning.
	if (ensure(QuerierPawn))
	{
		AAIController* Controller = Cast<AAIController>(QuerierPawn->GetController());
		check(Controller);
	
		AActor* TargetActor = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(NAME_TargetActor));
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, TargetActor);
	}
}
