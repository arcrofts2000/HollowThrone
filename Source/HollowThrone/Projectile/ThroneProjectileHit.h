// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThroneProjectileHit.generated.h"

class UNiagaraSystem;
class USphereComponent;
class UNiagaraComponent;
class UProjectileMovementComponent;

UCLASS(Abstract)
class HOLLOWTHRONE_API AThroneProjectileHit : public AActor
{
	GENERATED_BODY()
	
public:	

	AThroneProjectileHit();

	virtual void PostInitializeComponents() override;


protected:

	// Effects

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	// Components

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UNiagaraComponent> NiagaraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;


	// Functions

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
