// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "Projectile/ThroneProjectileBase.h"
#include "ThroneProjectileDash.generated.h"

/**
 * 
 */
UCLASS()
class HOLLOWTHRONE_API AThroneProjectileDash : public AThroneProjectileBase
{
	GENERATED_BODY()
	

public:

	AThroneProjectileDash();

	virtual void PostInitializeComponents() override;
};
