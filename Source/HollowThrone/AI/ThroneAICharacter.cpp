// Copyright - Adam Crofts


#include "AI/ThroneAICharacter.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"
#include "GameFramework/PawnMovementComponent.h"


AThroneAICharacter::AThroneAICharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UThroneAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

void AThroneAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AbilitySystemComponent->OnHealthChanged.AddDynamic(this, &AThroneAICharacter::OnHealthChanged);
}



float AThroneAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	AbilitySystemComponent->ApplyHealthChange(-ActualDamage);
	return ActualDamage;
}

void AThroneAICharacter::OnHealthChanged(float OldHealth, float NewHealth)
{
	if (NewHealth <= 0.f)
	{
		GetMovementComponent()->StopMovementImmediately();

		GetController()->UnPossess();
		SetLifeSpan(10.f);
		//PlayAnimMontage(DeathMontage);
	}
}