// Copyright - Adam Crofts


#include "AI/Task/ThroneBTService_CheckRangeTo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ThroneGameTypes.h"


UThroneBTService_CheckRangeTo::UThroneBTService_CheckRangeTo()
{
	TargetActorKey.SelectedKeyName = NAME_TargetActor;
}



void UThroneBTService_CheckRangeTo::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	check(BBComp);

	AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if (TargetActor)
	{
		FVector TargetLocation = TargetActor->GetActorLocation();

		AAIController* Controller = OwnerComp.GetAIOwner();
		APawn* OwnedPawn = Controller->GetPawn();
		check(OwnedPawn);


		float DistanceTo = FVector::Dist(TargetLocation, OwnedPawn->GetActorLocation());
		bool bWithinRange = DistanceTo < MaxAttackRange;

		bool bHasLineOfSight = Controller->LineOfSightTo(TargetActor);

		BBComp->SetValueAsBool(WithinRangeKey.SelectedKeyName, (bWithinRange && bHasLineOfSight));
	}
}