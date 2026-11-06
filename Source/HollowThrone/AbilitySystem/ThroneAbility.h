// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "ThroneAbility.generated.h"

class UThroneAbilitySystemComponent;

UCLASS(Blueprintable, Abstract)
class HOLLOWTHRONE_API UThroneAbility : public UObject
{
	GENERATED_BODY()
	

protected: 

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	FGameplayTag AbilityName;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	FGameplayTagContainer GrantedTags;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	FGameplayTagContainer BlockedTags;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	float CooldownTime = 0.f;


public:

	UFUNCTION()
	bool CanStart() const;

	UFUNCTION(BlueprintNativeEvent, Category = "Abilities")
	void StartAbility();

	UFUNCTION(BlueprintNativeEvent, Category = "Abilities")
	void StopAbility();

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	UThroneAbilitySystemComponent* GetOwningComponent() const;



	FORCEINLINE FGameplayTag GetAbilityName() const { return AbilityName; }

	FORCEINLINE float GetCooldownRemaining() const { return FMath::Max(0.0f, CooldownUntil - GetWorld()->GetTimeSeconds()); }

	UFUNCTION()
	FORCEINLINE bool IsRunning() const { return bIsRunning; }



protected:

	/* Time until Ability can be used again */
	UPROPERTY(Transient)
	float CooldownUntil = 0.f;

	UPROPERTY(Transient)
	bool bIsRunning = false;
};
