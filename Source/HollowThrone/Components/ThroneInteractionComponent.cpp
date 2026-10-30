// Copyright - Adam Crofts


#include "ThroneInteractionComponent.h"
#include "../Core/ThroneInteractionInterface.h"
#include "Engine/OverlapResult.h"
#include "ThroneGameTypes.h"

TAutoConsoleVariable<bool> CVarInteractionDebugDraw(TEXT("throne.interaction.debug"), false,
	TEXT("Draw debug render for Interaction Component, 1 = On / 0 = Off"), ECVF_Cheat);


UThroneInteractionComponent::UThroneInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	InteractionRadius = 300.0f;
	DirectionWeightMultiplier = 1.f;
	DistanceToWeightMultiplier = 1.f;
}

void UThroneInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool bEnableDebugDraw = CVarInteractionDebugDraw.GetValueOnGameThread();

	APlayerController* PC = CastChecked<APlayerController>(GetOwner());
	FVector Centre = PC->GetPawn()->GetActorLocation();
	FVector CameraLocation = PC->PlayerCameraManager->GetCameraLocation();

	TArray<FOverlapResult> Overlaps;
	ECollisionChannel CollisionChannel = COLLISION_INTERACTION;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(InteractionRadius);

	GetWorld()->OverlapMultiByChannel(Overlaps, Centre, FQuat::Identity, CollisionChannel, CollisionShape);

	if (bEnableDebugDraw)
		DrawDebugSphere(GetWorld(), Centre, InteractionRadius, 20, FColor::Green);

	ClosestActor = nullptr;
	float BestWeight = 0.0f;

	float InteractionRadiusSqrd = InteractionRadius * InteractionRadius;

	for (FOverlapResult& Overlap : Overlaps)
	{
		// Getting the origin (centre of the actor) rather than gettin Actor Location
		// Slightly worse performance wise, but more accurate for interaction detection
		FVector Origin;
		FVector BoxExtent;
		Overlap.GetActor()->GetActorBounds(true, Origin, BoxExtent);

		FVector OverlapDirection = (Origin - CameraLocation).GetSafeNormal();
		
		// Calculate the dot product of the angle the player is looking at vs the intended object, and then
		// normalise it so that the value never goes below 0
		float DotProduct = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());
		float NormalisedDotProduct = DotProduct * 0.5f + 0.5f;

		// Calculate the distance between the Player and the intended object, and then normalise it by dividing by 
		// the interaction radius (as this is the furthest away the player can be to interact)
		/*							Set to Squared for Performance optimisation							*/
		float DistanceToSqrd = (Origin - Centre).SizeSquared();
		float NormalisedDistanceTo = DistanceToSqrd / InteractionRadiusSqrd;

		float Weight = (NormalisedDotProduct * DirectionWeightMultiplier) + (NormalisedDistanceTo * DistanceToWeightMultiplier);

		if (Weight > BestWeight)
		{
			BestWeight = Weight;
			ClosestActor = Overlap.GetActor();
		}
	}

	if (ClosestActor && bEnableDebugDraw)
	{
		DrawDebugBox(GetWorld(), ClosestActor->GetActorLocation(), FVector(50.0f), FColor::Red);
	}
}

void UThroneInteractionComponent::Interact()
{
	IThroneInteractionInterface::Execute_Interact(ClosestActor);
}