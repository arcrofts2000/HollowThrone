// Copyright - Adam Crofts


#include "AbilitySystem/Abilities/ThroneAbility_Projectile.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"
#include "Projectile/ThroneProjectileBase.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "ThroneGameTypes.h"

UThroneAbility_Projectile::UThroneAbility_Projectile()
{
	RightHandSocketName = "Muzzle_01";
	AttackDelayTime = 0.2f;
	ProjectileTraceDistance = 5000.f;

	CooldownTime = 0.5f;
}

void UThroneAbility_Projectile::StartAbility_Implementation()
{
	Super::StartAbility_Implementation();

	UThroneAbilitySystemComponent* ASC = GetOwningComponent();
	ACharacter* Character = CastChecked<ACharacter>(ASC->GetOwner());

	Character->PlayAnimMontage(AttackMontage);

	UNiagaraFunctionLibrary::SpawnSystemAttached(CastEffect, Character->GetMesh(), RightHandSocketName,
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);

	UGameplayStatics::PlaySound2D(this, CastSound);

	FTimerHandle AttackTimerHandle;
	FTimerDelegate AttackDelegate;

	AttackDelegate.BindUObject(this, &ThisClass::AttackAnimTimerElapsed, Character);
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, AttackDelegate, 1.f, false, AttackDelayTime);

}


void UThroneAbility_Projectile::AttackAnimTimerElapsed(ACharacter* Character)
{
	FVector SpawnLocation = Character->GetMesh()->GetSocketLocation(RightHandSocketName);
	FRotator SpawnRotation = Character->GetControlRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = Character;

	FHitResult Hit;

	FVector EyeLocation;
	FRotator EyeRotation;
	Character->GetController()->GetPlayerViewPoint(EyeLocation, EyeRotation);
	
	FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * ProjectileTraceDistance);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Character);

	if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, COLLISION_PROJECTILE, Params))
	{
		// If linetrace is successful, adjust the rotation to meet the target
		// Without this, the projectile would spawn slightly off centre

		SpawnRotation = (Hit.Location - SpawnLocation).Rotation();
	}
	else
	{
		SpawnRotation = (TraceEnd - SpawnLocation).Rotation();
	}

	AThroneProjectileBase* SpawnedProjectile = GetWorld()->SpawnActor<AThroneProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	Character->MoveIgnoreActorAdd(SpawnedProjectile);

	StopAbility();
}