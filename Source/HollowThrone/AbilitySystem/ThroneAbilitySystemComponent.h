// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "ThroneAbilitySystemComponent.generated.h"





DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, OldHealth, float, NewHealth);



class UThroneAbility;
class UThroneAttributeSet;
struct FThroneAttribute;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOLLOWTHRONE_API UThroneAbilitySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UThroneAbilitySystemComponent();

	virtual void InitializeComponent() override;
	void InitializeAttributes();
	void InitializeAbilities();

	

	bool ApplyHealthChange(float HealthDelta);

	float GetHealthPercent() const;

	FThroneAttribute* GetAttribute(FGameplayTag InAttributeTag);

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnHealthChangedSignature OnHealthChanged;


	// Abilities

	FGameplayTagContainer ActiveGameplayTags;

	void StartAbility(FGameplayTag InAbilityName);
	void StopAbility(FGameplayTag InAbilityName);
	
	void GrantAbility(TSubclassOf<UThroneAbility> AbilityToGrant);

	


protected:

	UPROPERTY()
	TObjectPtr<UThroneAttributeSet> AttributeSet;

	TMap<FGameplayTag, FThroneAttribute*> CachedAttributes;

	/* NoClear prevents this from being set to NULL */
	UPROPERTY(EditAnywhere, Category = "Attributes", NoClear)
	TSubclassOf<UThroneAttributeSet> AttributeSetClass;


	UPROPERTY()
	TArray<TObjectPtr<UThroneAbility>> Abilities;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UThroneAbility>> DefaultAbilities;


	
		
};
