// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ThroneAICharacter.generated.h"

class UThroneAbilitySystemComponent;
struct FGameplayTag;

UCLASS()
class HOLLOWTHRONE_API AThroneAICharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AThroneAICharacter();



protected:

	// Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UThroneAbilitySystemComponent> AbilitySystemComponent;


	// Functions

	UFUNCTION()
	void OnHealthChanged(FGameplayTag AttributeTag, float OldHealth, float NewHealth);


public:

	virtual void PostInitializeComponents() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
