// Copyright - Adam Crofts


#include "AbilitySystem/ThroneAbilitySystemComponent.h"
#include "AbilitySystem/ThroneAbility.h"


UThroneAbilitySystemComponent::UThroneAbilitySystemComponent()
{
	// Must be set in order to initialize the component on Actor spawn and call InitializeComponent()
	bWantsInitializeComponent = true;
}

void UThroneAbilitySystemComponent::InitializeComponent()
{
	Super::InitializeComponent();

	for (TSubclassOf<UThroneAbility> AbilityClass : DefaultAbilities)
	{
		// Ensured so that we don't try to grant a null ability class, which would cause a crash.
		if (ensureMsgf(AbilityClass, TEXT("Failed to grant ability, AbilityClass is null.")))
		{
			GrantAbility(AbilityClass);
		}
	}
}


void UThroneAbilitySystemComponent::GrantAbility(TSubclassOf<UThroneAbility> AbilityToGrant)
{
	UThroneAbility* NewAbility = NewObject<UThroneAbility>(this, AbilityToGrant);
	Abilities.Add(NewAbility);
}

void UThroneAbilitySystemComponent::StartAbility(FGameplayTag InAbilityName)
{
	for (UThroneAbility* Ability : Abilities)
	{
		if (Ability->GetAbilityName() == InAbilityName)
		{
			if (Ability->CanStart())
			{
				Ability->StartAbility();
			}

			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No Ability found with name: %s"), *InAbilityName.ToString());
}


void UThroneAbilitySystemComponent::StopAbility(FGameplayTag InAbilityName)
{
	for (UThroneAbility* Ability : Abilities)
	{
		if (Ability->GetAbilityName() == InAbilityName)
		{
			Ability->StopAbility();
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No Ability found with name: %s"), *InAbilityName.ToString());
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