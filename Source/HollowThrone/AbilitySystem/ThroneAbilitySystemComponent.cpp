// Copyright - Adam Crofts


#include "AbilitySystem/ThroneAbilitySystemComponent.h"


UThroneAbilitySystemComponent::UThroneAbilitySystemComponent()
{

}

void UThroneAbilitySystemComponent::ApplyHealthChange(float HealthDelta)
{
	float OldHealth = AttributeSet.Health;
	
	AttributeSet.Health = FMath::Clamp(AttributeSet.Health += HealthDelta, 0.f, AttributeSet.MaxHealth);

	if (!FMath::IsNearlyEqual(OldHealth, AttributeSet.Health))
		OnHealthChanged.Broadcast(OldHealth, AttributeSet.Health);

	UE_LOG(LogTemp, Log, TEXT("New Health: %f, MaxHealth: %f"), AttributeSet.Health, AttributeSet.MaxHealth);
}