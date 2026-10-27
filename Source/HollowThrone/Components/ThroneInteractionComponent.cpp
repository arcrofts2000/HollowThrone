// Copyright - Adam Crofts


#include "ThroneInteractionComponent.h"


UThroneInteractionComponent::UThroneInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UThroneInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UThroneInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

