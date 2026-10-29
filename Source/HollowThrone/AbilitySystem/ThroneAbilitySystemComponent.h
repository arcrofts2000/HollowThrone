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



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOLLOWTHRONE_API UThroneAbilitySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UThroneAbilitySystemComponent();

	void ApplyHealthChange(float HealthDelta);

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnHealthChangedSignature OnHealthChanged;


protected:

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FThroneAttributeSet AttributeSet;
		
};
