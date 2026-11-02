// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "Pickup/ThronePickupBase.h"
#include "ThronePickupHealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class HOLLOWTHRONE_API AThronePickupHealthPotion : public AThronePickupBase
{
	GENERATED_BODY()

public:

	AThronePickupHealthPotion();
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float AmountToIncrease;
	
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
