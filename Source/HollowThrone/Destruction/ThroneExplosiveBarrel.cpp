// Copyright - Adam Crofts


#include "ThroneExplosiveBarrel.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


AThroneExplosiveBarrel::AThroneExplosiveBarrel()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionProfileName("PhysicsActor");

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->SetupAttachment(MeshComponent);
	RadialForceComponent->bAutoActivate = false;
	RadialForceComponent->bIgnoreOwningActor = true;
	RadialForceComponent->bImpulseVelChange = false;
	RadialForceComponent->Radius = 1000.f;
	RadialForceComponent->ImpulseStrength = 100000.f;

	FireEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireEffect"));
	FireEffect->SetupAttachment(MeshComponent);
	FireEffect->bAutoActivate = false;

	FireSound = CreateDefaultSubobject<UAudioComponent>(TEXT("FireSound"));
	FireSound->SetupAttachment(MeshComponent);
	FireSound->bAutoActivate = false;
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

		GetWorldTimerManager().SetTimer(ExplodeHandle, this, &AThroneExplosiveBarrel::Explode, ExplosionDelay);

		// Effects
		FireEffect->Activate();
		FireSound->Activate();
	}
}

void AThroneExplosiveBarrel::Explode()
{
	bExploded = true;
	FireEffect->Deactivate();
	FireSound->Deactivate();

	// Effects
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());

	MeshComponent->AddImpulse(FVector::UpVector * 750, NAME_None, true);
	MeshComponent->AddAngularImpulseInDegrees(FVector::LeftVector * 500, NAME_None, true);

	// Gameplay
	RadialForceComponent->FireImpulse();
}