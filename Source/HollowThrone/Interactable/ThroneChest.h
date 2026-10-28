// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThroneChest.generated.h"

UCLASS()
class HOLLOWTHRONE_API AThroneChest : public AActor
{
	GENERATED_BODY()
	
public:	

	AThroneChest();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
