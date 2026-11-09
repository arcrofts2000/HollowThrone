// Copyright - Adam Crofts


#include "Core/ThroneGameplayStatics.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"
#include "AbilitySystem/ThroneAttributeSet.h"
#include "ThroneGameplayTags.h"

bool UThroneGameplayStatics::IsFullHealth(UThroneAbilitySystemComponent* AbilitySystemComponent)
{
	FThroneAttribute* Health = AbilitySystemComponent->GetAttribute(ThroneGameplayTags::Attribute_Health);
	FThroneAttribute* MaxHealth = AbilitySystemComponent->GetAttribute(ThroneGameplayTags::Attribute_MaxHealth);

	return FMath::IsNearlyEqual(Health->GetValue(), MaxHealth->GetValue());
}

float UThroneGameplayStatics::GetHealthPercent(UThroneAbilitySystemComponent* AbilitySystemComponent)
{
	FThroneAttribute* Health = AbilitySystemComponent->GetAttribute(ThroneGameplayTags::Attribute_Health);
	FThroneAttribute* MaxHealth = AbilitySystemComponent->GetAttribute(ThroneGameplayTags::Attribute_MaxHealth);

	return ((Health->GetValue() / MaxHealth->GetValue()) * 100.f);
}