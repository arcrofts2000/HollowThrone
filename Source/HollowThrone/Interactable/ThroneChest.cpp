// Copyright - Adam Crofts


#include "ThroneChest.h"
#include "Components/StaticMeshComponent.h"


AThroneChest::AThroneChest()
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
	BaseMesh->SetCollisionProfileName("Interaction");

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);
	LidMesh->SetCollisionProfileName("NoCollision");

	CurrentLidPitch = 0.f;
	TargetLidPitch = 120.f;
	LidOpenSpeed = 60.f;
}

void AThroneChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentLidPitch = FMath::FInterpConstantTo(CurrentLidPitch, TargetLidPitch, DeltaTime, LidOpenSpeed);
	LidMesh->SetRelativeRotation(FRotator(CurrentLidPitch, 0.f, 0.f));

	if (FMath::IsNearlyEqual(CurrentLidPitch, TargetLidPitch))
	{
		SetActorTickEnabled(false);
	}
}


/* Begin Interaction Interface */

void AThroneChest::Interact()
{
	SetActorTickEnabled(true);
}

/* End Interaction Interface */