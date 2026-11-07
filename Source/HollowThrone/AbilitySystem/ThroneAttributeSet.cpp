// Copyright - Adam Crofts


#include "AbilitySystem/ThroneAttributeSet.h"

UThroneHealthAttributeSet::UThroneHealthAttributeSet()
{
	Health = FThroneAttribute(100.f);
	MaxHealth = FThroneAttribute(Health.GetValue());
}
