// Copyright - Adam Crofts


#include "AbilitySystem/ThroneAttributeSet.h"

UThroneHealthAttributeSet::UThroneHealthAttributeSet()
{
	Health = FThroneAttribute(100.f);
	MaxHealth = FThroneAttribute(Health.GetValue());
}

void UThroneHealthAttributeSet::PostAttributeChange()
{
	Health.Base = FMath::Clamp(Health.Base, 0.f, MaxHealth.GetValue());
}
