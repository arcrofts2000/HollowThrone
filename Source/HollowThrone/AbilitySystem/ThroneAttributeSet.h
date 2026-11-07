// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ThroneAttributeSet.generated.h"



USTRUCT()
struct FThroneAttribute
{
	GENERATED_BODY()

	FThroneAttribute() {}

	FThroneAttribute(float InBase) 
		: Base(InBase) {}


	UPROPERTY(EditAnywhere)
	float Base = 0.f;

	UPROPERTY(Transient)
	float Modifier = 0.f;

	float GetValue()
	{
		return Base + Modifier;
	}
};



UCLASS()
class HOLLOWTHRONE_API UThroneAttributeSet : public UObject
{
	GENERATED_BODY()
	
};



UCLASS()
class UThroneHealthAttributeSet : public UThroneAttributeSet
{
	GENERATED_BODY()

public:

	UThroneHealthAttributeSet();

	UPROPERTY(EditAnywhere, Category = "Attributes")
	FThroneAttribute Health;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	FThroneAttribute MaxHealth;

};