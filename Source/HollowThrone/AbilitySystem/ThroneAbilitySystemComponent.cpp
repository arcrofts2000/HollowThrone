// Copyright - Adam Crofts


#include "AbilitySystem/ThroneAbilitySystemComponent.h"


UThroneAbilitySystemComponent::UThroneAbilitySystemComponent()
{

}

/* returns a boolean variable indicating whether the health has changed enough */
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

/* Returns the health percentage as a value between 0 and 100 */
float UThroneAbilitySystemComponent::GetHealthPercent() const
{
	return (AttributeSet.Health / AttributeSet.MaxHealth) * 100.f;
}