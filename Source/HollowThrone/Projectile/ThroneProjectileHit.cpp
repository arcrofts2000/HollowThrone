// Copyright - Adam Crofts


#include "ThroneProjectileHit.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AThroneProjectileHit::AThroneProjectileHit()
{
	
}

void AThroneProjectileHit::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
	SphereComponent->OnComponentHit.AddDynamic(this, &AThroneProjectileHit::OnHit);
}

void AThroneProjectileHit::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//@TODO: Temporary solution - Will be replaced with a more robust damage system in the future
	FVector HitDirection = GetActorRotation().Vector();

	UGameplayStatics::ApplyPointDamage(OtherActor, 10.f, HitDirection, Hit, GetInstigatorController(), this, DamageTypeClass);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation(), FRotator::ZeroRotator);

	Destroy();
}