// Copyright - Adam Crofts


#include "AI/ThroneAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

AThroneAIController::AThroneAIController()
{

}


void AThroneAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(AIBehaviourTree);

	FName TargetActor = FName("TargetActor");
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	check(PlayerPawn);

	GetBlackboardComponent()->SetValueAsObject(TargetActor, PlayerPawn);
}