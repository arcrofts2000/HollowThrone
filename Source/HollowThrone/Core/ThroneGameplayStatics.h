// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ThroneGameplayStatics.generated.h"

class UThroneAbilitySystemComponent;

UCLASS()
class HOLLOWTHRONE_API UThroneGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	static bool IsFullHealth(UThroneAbilitySystemComponent* AbilitySystemComponent);

	static float GetHealthPercent(UThroneAbilitySystemComponent* AbilitySystemComponent);
};
