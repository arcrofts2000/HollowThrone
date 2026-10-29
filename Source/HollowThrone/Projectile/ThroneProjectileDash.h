// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "Projectile/ThroneProjectileBase.h"
#include "ThroneProjectileDash.generated.h"

class UNiagaraSystem;
struct FTimerHandle;

UCLASS(Abstract)
class HOLLOWTHRONE_API AThroneProjectileDash : public AThroneProjectileBase
{
	GENERATED_BODY()
	

public:

	AThroneProjectileDash();

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;


protected:

	// Requirements

	UPROPERTY(EditDefaultsOnly, Category = "Dash")
	float ExplodeDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Dash")
	float TeleportDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ImplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;


	// Functions

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void Explode();
	void Teleport();

	FTimerHandle ExplodeHandle;
};
