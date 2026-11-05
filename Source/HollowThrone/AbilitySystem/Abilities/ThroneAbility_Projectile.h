// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ThroneAbility.h"
#include "ThroneAbility_Projectile.generated.h"

class AThroneProjectileBase;
class UAnimMontage;
class UNiagaraSystem;
class USoundBase;
class ACharacter;

UCLASS(Abstract)
class HOLLOWTHRONE_API UThroneAbility_Projectile : public UThroneAbility
{
	GENERATED_BODY()
	
public:

	UThroneAbility_Projectile();

	virtual void StartAbility_Implementation() override;



protected:

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	FName RightHandSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AThroneProjectileBase> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TObjectPtr<UNiagaraSystem> CastEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TObjectPtr<USoundBase> CastSound;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float AttackDelayTime;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float ProjectileTraceDistance;


	// Functions

	void AttackAnimTimerElapsed(ACharacter* Character);
};
