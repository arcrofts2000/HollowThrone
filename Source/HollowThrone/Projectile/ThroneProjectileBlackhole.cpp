// Copyright - Adam Crofts


#include "Projectile/ThroneProjectileBlackhole.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/SphereComponent.h"


AThroneProjectileBlackhole::AThroneProjectileBlackhole()
{
	BlackholeForce = -3000000.f;

	SphereComponent->SetCollisionProfileName("NoCollision");

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->SetupAttachment(GetRootComponent());
	RadialForceComponent->bAutoActivate = true;
	RadialForceComponent->ForceStrength = BlackholeForce;
	RadialForceComponent->bIgnoreOwningActor = true;

	CollisionSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphereComponent"));
	CollisionSphereComponent->SetupAttachment(GetRootComponent());

	SetLifeSpan(5.f);
}


void AThroneProjectileBlackhole::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
	CollisionSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AThroneProjectileBlackhole::OnBlackholeOverlap);
}



void AThroneProjectileBlackhole::OnBlackholeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics())
		OtherActor->Destroy();
}