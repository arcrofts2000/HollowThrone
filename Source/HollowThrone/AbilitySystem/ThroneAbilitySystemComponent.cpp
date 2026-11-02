// Copyright - Adam Crofts


#include "AbilitySystem/ThroneAbilitySystemComponent.h"


UThroneAbilitySystemComponent::UThroneAbilitySystemComponent()
{

}

bool UThroneAbilitySystemComponent::ApplyHealthChange(float HealthDelta)
{
	float OldHealth = AttributeSet.Health;
	
	AttributeSet.Health = FMath::Clamp(AttributeSet.Health += HealthDelta, 0.f, AttributeSet.MaxHealth);
	UE_LOG(LogTemp, Log, TEXT("New Health: %f, MaxHealth: %f"), AttributeSet.Health, AttributeSet.MaxHealth);


	if (!FMath::IsNearlyEqual(OldHealth, AttributeSet.Health))
	{
		// Notify listeners only when health changed significantly
		OnHealthChanged.Broadcast(OldHealth, AttributeSet.Health);
		return true;
	}

	// Health did not change enough
	return false;
}