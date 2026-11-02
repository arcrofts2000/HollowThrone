// Copyright - Adam Crofts


#include "Pickup/ThronePickupBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


AThronePickupBase::AThronePickupBase()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetCollisionProfileName("NoCollision");

	SphereCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionComponent"));
	SphereCollisionComponent->SetupAttachment(StaticMeshComponent);
	SphereCollisionComponent->SetCollisionProfileName("Pickup");
}


void AThronePickupBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AThronePickupBase::BeginOverlap);
}

void AThronePickupBase::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
	Destroy();
}