// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "Projectile/ThroneProjectileBase.h"
#include "ThroneProjectileBlackhole.generated.h"

/**
 * 
 */
UCLASS()
class HOLLOWTHRONE_API AThroneProjectileBlackhole : public AThroneProjectileBase
{
	GENERATED_BODY()
	
public:

	AThroneProjectileBlackhole();

	virtual void PostInitializeComponents() override;
};
