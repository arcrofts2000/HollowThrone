// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThroneProjectileBase.generated.h"

class USphereComponent;
class UNiagaraComponent;
class UAudioComponent;
class UProjectileMovementComponent;

UCLASS(Abstract)
class HOLLOWTHRONE_API AThroneProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	

	AThroneProjectileBase();


protected:

	// Components

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UNiagaraComponent> NiagaraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<UAudioComponent> TravelAudioComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

};
