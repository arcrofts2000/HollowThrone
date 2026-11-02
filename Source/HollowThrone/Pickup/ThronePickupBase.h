// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThronePickupBase.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class USoundBase;

UCLASS()
class HOLLOWTHRONE_API AThronePickupBase : public AActor
{
	GENERATED_BODY()
	
public:	

	AThronePickupBase();

	virtual void PostInitializeComponents() override;


protected:

	// Effects

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<USoundBase> PickupSound;


	// Functions

	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	// Components

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> SphereCollisionComponent;

};
