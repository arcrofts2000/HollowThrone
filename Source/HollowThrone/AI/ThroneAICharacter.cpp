// Copyright - Adam Crofts


#include "AI/ThroneAICharacter.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "ThroneGameplayTags.h"


AThroneAICharacter::AThroneAICharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UThroneAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

void AThroneAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FOnAttributeChangedSignature& Event = AbilitySystemComponent->GetAttributeDelegate(ThroneGameplayTags::Attribute_Health);
	Event.AddUObject(this, &AThroneAICharacter::OnHealthChanged);
}



float AThroneAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	AbilitySystemComponent->ApplyAttributeChange(ThroneGameplayTags::Attribute_Health, -ActualDamage, EAttributeModifyType::Base);
	return ActualDamage;
}

void AThroneAICharacter::OnHealthChanged(FGameplayTag AttributeTag, float OldHealth, float NewHealth)
{
	if (NewHealth <= 0.f)
	{
		GetMovementComponent()->StopMovementImmediately();

		GetController()->UnPossess();
		SetLifeSpan(10.f);
		//PlayAnimMontage(DeathMontage);
	}
}