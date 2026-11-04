// Copyright - Adam Crofts


#include "AI/Task/ThroneBTTask_RangedAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Projectile/ThroneProjectileBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "ThroneGameTypes.h"

UThroneBTTask_RangedAttack::UThroneBTTask_RangedAttack()
{
	TargetActorKey.SelectedKeyName = NAME_TargetActor;
	FireSound = CreateDefaultSubobject<USoundBase>(TEXT("FireSound"));
}



EBTNodeResult::Type UThroneBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	ACharacter* OwnedPawn = Cast<ACharacter>(Controller->GetPawn());
	check(OwnedPawn);

	FVector SpawnLocation = OwnedPawn->GetMesh()->GetSocketLocation(MuzzleSocketName);

	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if (!IsValid(TargetActor))
	{
		return EBTNodeResult::Failed;
	}

	FVector Direction = TargetActor->GetActorLocation() - SpawnLocation;
	FRotator SpawnRotation = Direction.Rotation();

	SpawnRotation.Pitch += FMath::FRandRange(0.f, BulletSpread);
	SpawnRotation.Yaw += FMath::FRandRange(-BulletSpread, BulletSpread);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = OwnedPawn;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* SpawnedProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

	UGameplayStatics::PlaySoundAtLocation(this, FireSound, SpawnLocation);

	return SpawnedProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}