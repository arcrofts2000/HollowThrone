// Copyright - Adam Crofts


#include "Projectile/ThroneProjectileDash.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"


AThroneProjectileDash::AThroneProjectileDash()
{
	ExplodeDelay = 0.2f;
	TeleportDelay = 0.2f;
}


void AThroneProjectileDash::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
	SphereComponent->OnComponentHit.AddDynamic(this, &AThroneProjectileDash::OnHit);
}

void AThroneProjectileDash::BeginPlay()
{
	Super::BeginPlay();


	GetWorldTimerManager().SetTimer(ExplodeHandle, this, &AThroneProjectileDash::Explode, ExplodeDelay);
}


void AThroneProjectileDash::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GetWorldTimerManager().ClearTimer(ExplodeHandle);

	GetWorldTimerManager().SetTimer(ExplodeHandle, this, &AThroneProjectileDash::Explode, ExplodeDelay);
}


void AThroneProjectileDash::Explode()
{
	// Stop projectile movement from continuing movement.
	ProjectileMovementComponent->StopMovementImmediately();

	// Play Explosion effect
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImplosionEffect, GetActorLocation());

	// Set new timer for teleporting player.
	FTimerHandle TeleportHandle;
	GetWorldTimerManager().SetTimer(TeleportHandle, this, &AThroneProjectileDash::Teleport, TeleportDelay);
}

void AThroneProjectileDash::Teleport()
{
	// Play Explosion effect
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());

	// Teleport player and destroy self
	GetInstigator()->TeleportTo(GetActorLocation(), GetInstigator()->GetActorRotation());

	Destroy();
}

