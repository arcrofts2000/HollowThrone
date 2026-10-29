// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "ThroneProjectileBase.h"
#include "ThroneProjectileHit.generated.h"

class UDamageType;
class UNiagaraSystem;
class USoundBase;

UCLASS(Abstract)
class HOLLOWTHRONE_API AThroneProjectileHit : public AThroneProjectileBase
{
	GENERATED_BODY()
	
public:	

	AThroneProjectileHit();

	virtual void PostInitializeComponents() override;


protected:

	// Damage

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DamageTypeClass;


	// Effects

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundBase> ExplosionSound;


	// Functions

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
