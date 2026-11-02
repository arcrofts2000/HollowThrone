// Copyright - Adam Crofts


#include "Pickup/ThronePickupHealthPotion.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"


AThronePickupHealthPotion::AThronePickupHealthPotion()
{
	AmountToIncrease = 10.f;
}

void AThronePickupHealthPotion::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UThroneAbilitySystemComponent* ASC = OtherActor->GetComponentByClass<UThroneAbilitySystemComponent>())
	{
		// Call Apply Health change,
		// base functionality (destroy self and play sound) should only be valid if Health has changed
		if (ASC->ApplyHealthChange(AmountToIncrease))
		{
			// Call this after added functionality
			Super::BeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
		}
	}
}