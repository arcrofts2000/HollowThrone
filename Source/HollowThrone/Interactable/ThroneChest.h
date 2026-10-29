// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "../Core/ThroneInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "ThroneChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class HOLLOWTHRONE_API AThroneChest : public AActor, public IThroneInteractionInterface
{
	GENERATED_BODY()
	
public:	

	AThroneChest();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LidMesh;

	float CurrentLidPitch;

	UPROPERTY(EditAnywhere, Category = "Chest")
	float TargetLidPitch;

	UPROPERTY(EditAnywhere, Category = "Chest")
	float LidOpenSpeed;

	UFUNCTION(BlueprintImplementableEvent)
	void OnChestAnimFinished();


public:	

	virtual void Tick(float DeltaTime) override;

	
	/* Begin Interaction Interface */

	virtual void Interact_Implementation() override;
	
	/* End Interaction Interface */

};
