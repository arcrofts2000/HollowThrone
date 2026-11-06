// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThroneAbilitySystemComponent.generated.h"




USTRUCT(BlueprintType)
struct FThroneAttributeSet
{
	GENERATED_BODY()
	FThroneAttributeSet()
		: Health(100.f),
	MaxHealth(100.f) {}

	UPROPERTY(BlueprintReadOnly)
	float Health;

	UPROPERTY(BlueprintReadOnly)
	float MaxHealth;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, OldHealth, float, NewHealth);



struct FGameplayTag;
class UThroneAbility;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOLLOWTHRONE_API UThroneAbilitySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UThroneAbilitySystemComponent();

	virtual void InitializeComponent() override;

	void StartAbility(FGameplayTag InAbilityName);
	void StopAbility(FGameplayTag InAbilityName);

	bool ApplyHealthChange(float HealthDelta);

	float GetHealthPercent() const;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnHealthChangedSignature OnHealthChanged;


	// Abilities

	void GrantAbility(TSubclassOf<UThroneAbility> AbilityToGrant);


protected:

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FThroneAttributeSet AttributeSet;

	UPROPERTY()
	TArray<TObjectPtr<UThroneAbility>> Abilities;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UThroneAbility>> DefaultAbilities;


	
		
};
