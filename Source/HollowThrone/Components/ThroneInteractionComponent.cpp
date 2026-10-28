// Copyright - Adam Crofts


#include "ThroneInteractionComponent.h"
#include "Engine/OverlapResult.h"


UThroneInteractionComponent::UThroneInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	InteractionRadius = 300.0f;
}

void UThroneInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APlayerController* PC = CastChecked<APlayerController>(GetOwner());
	FVector Centre = PC->GetPawn()->GetActorLocation();

	TArray<FOverlapResult> Overlaps;
	ECollisionChannel CollisionChannel = ECC_Visibility;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(InteractionRadius);

	GetWorld()->OverlapMultiByChannel(Overlaps, Centre, FQuat::Identity, CollisionChannel, CollisionShape);

	DrawDebugSphere(GetWorld(), Centre, InteractionRadius, 20, FColor::Green);

	AActor* ClosestActor = nullptr;
	float HighestDotProduct = -1.0f;

	for (FOverlapResult& Overlap : Overlaps)
	{
		FVector OverlapDirection = (Overlap.GetActor()->GetActorLocation() - Centre).GetSafeNormal();

		float DotProduct = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());

		if (DotProduct > HighestDotProduct)
		{
			HighestDotProduct = DotProduct;
			ClosestActor = Overlap.GetActor();
		}
	}

	if (ClosestActor)
	{
		DrawDebugBox(GetWorld(), ClosestActor->GetActorLocation(), FVector(50.0f), FColor::Red);
	}
}

