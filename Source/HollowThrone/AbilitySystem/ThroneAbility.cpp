// Copyright - Adam Crofts


#include "AbilitySystem/ThroneAbility.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"

void UThroneAbility::StartAbility_Implementation()
{
	
}

void UThroneAbility::StopAbility_Implementation()
{
	// Made as an if statement incase World is invalid (as it can be with Blueprints)
	float GameTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;

	UE_LOGFMT(LogTemp, Log, "Stopped Ability: {AbilityName} - {WorldTime}",
		("AbilityName", AbilityName),
		("WorldTime", GameTime));
}

UThroneAbilitySystemComponent* UThroneAbility::GetOwningComponent() const
{
	return Cast<UThroneAbilitySystemComponent>(GetOuter());
}

