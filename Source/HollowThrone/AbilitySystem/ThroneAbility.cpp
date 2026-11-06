// Copyright - Adam Crofts


#include "AbilitySystem/ThroneAbility.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"


bool UThroneAbility::CanStart() const
{
	// Check if the ability is on cooldown
	if (GetCooldownRemaining() > 0.f)
	{
		UE_LOG(LogTemp, Log, TEXT("Cooldown Remaining: %f"), GetCooldownRemaining());
		return false;
	}

	// Check if the ability is already running
	if (bIsRunning)
	{
		UE_LOG(LogTemp, Log, TEXT("Ability is already running: %s"), *AbilityName.ToString());
		return false;
	}

	if (GetOwningComponent()->ActiveGameplayTags.HasAny(BlockedTags))
	{
		UE_LOG(LogTemp, Log, TEXT("Ability is blocked: %s"), *AbilityName.ToString());
		return false;
	}

	return true;
}



void UThroneAbility::StartAbility_Implementation()
{
	bIsRunning = true;

	GetOwningComponent()->ActiveGameplayTags.AppendTags(GrantedTags);
}

void UThroneAbility::StopAbility_Implementation()
{
	bIsRunning = false;

	// Made as an if statement incase World is invalid (as it can be with Blueprints)
	float GameTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;

	UE_LOGFMT(LogTemp, Log, "Stopped Ability: {AbilityName} - {WorldTime}",
		("AbilityName", AbilityName.ToString()),
		("WorldTime", GameTime));

	CooldownUntil = GetWorld()->GetTimeSeconds() + CooldownTime;
	GetOwningComponent()->ActiveGameplayTags.RemoveTags(GrantedTags);
}

UThroneAbilitySystemComponent* UThroneAbility::GetOwningComponent() const
{
	return Cast<UThroneAbilitySystemComponent>(GetOuter());
}

