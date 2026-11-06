// Copyright - Adam Crofts


#include "AbilitySystem/ThroneAbility.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"


bool UThroneAbility::CanStart() const
{
	if (GetCooldownRemaining() > 0.f)
	{
		UE_LOG(LogTemp, Log, TEXT("Cooldown Remaining: %f"), GetCooldownRemaining());
		return false;
	}

	return true;
}



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

	CooldownUntil = GetWorld()->GetTimeSeconds() + CooldownTime;
}

UThroneAbilitySystemComponent* UThroneAbility::GetOwningComponent() const
{
	return Cast<UThroneAbilitySystemComponent>(GetOuter());
}

