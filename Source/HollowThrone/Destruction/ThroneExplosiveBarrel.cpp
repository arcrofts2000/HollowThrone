// Copyright - Adam Crofts


#include "ThroneExplosiveBarrel.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"


AThroneExplosiveBarrel::AThroneExplosiveBarrel()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetSimulatePhysics(true);

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));

	FireEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireEffect"));
	FireEffect->SetupAttachment(MeshComponent);
	FireEffect->bAutoActivate = false;
}

void AThroneExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	OnTakeAnyDamage.AddDynamic(this, &AThroneExplosiveBarrel::OnTakeDamage);
}

void AThroneExplosiveBarrel::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (!bExploded)
	{
		FTimerHandle ExplodeHandle;

		GetWorldTimerManager().SetTimer(ExplodeHandle, this, &AThroneExplosiveBarrel::Explode, 3.f);

		// Effects
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation(), FRotator::ZeroRotator);
		FireEffect->Activate();
	}
}

void AThroneExplosiveBarrel::Explode()
{
	FireEffect->Deactivate();
	bExploded = true;

	// Effects
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());

	// Gameplay
	RadialForceComponent->FireImpulse();
}