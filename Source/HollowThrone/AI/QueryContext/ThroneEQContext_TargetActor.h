// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "ThroneEQContext_TargetActor.generated.h"

/**
 * 
 */
UCLASS()
class HOLLOWTHRONE_API UThroneEQContext_TargetActor : public UEnvQueryContext
{
	GENERATED_BODY()
	
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
};
