// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ThroneAbility.generated.h"

class UThroneAbilitySystemComponent;

UCLASS(Blueprintable, Abstract)
class HOLLOWTHRONE_API UThroneAbility : public UObject
{
	GENERATED_BODY()
	

protected: 

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	FName AbilityName = FName("PrimaryAttack");


public:

	UFUNCTION(BlueprintNativeEvent, Category = "Abilities")
	void StartAbility();

	UFUNCTION(BlueprintNativeEvent, Category = "Abilities")
	void StopAbility();

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	UThroneAbilitySystemComponent* GetOwningComponent() const;

	FORCEINLINE FName GetAbilityName() const { return AbilityName; }
};
