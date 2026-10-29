// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "Projectile/ThroneProjectileBase.h"
#include "ThroneProjectileBlackhole.generated.h"

class URadialForceComponent;
class USphereComponent;

UCLASS(Abstract)
class HOLLOWTHRONE_API AThroneProjectileBlackhole : public AThroneProjectileBase
{
	GENERATED_BODY()
	
public:

	AThroneProjectileBlackhole();

	virtual void PostInitializeComponents() override;


protected:

	// Components

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> CollisionSphereComponent;


	// Important extras

	/* Must be a negative number to suck objects in */
	UPROPERTY(EditDefaultsOnly, Category = "Blackhole")
	float BlackholeForce;


	// Functions

	UFUNCTION()
	void OnBlackholeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
