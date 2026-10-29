// Copyright - Adam Crofts


#include "ThroneCharacter.h"
#include "Projectile/ThroneProjectileBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "Engine.h"
#include "NiagaraFunctionLibrary.h"

AThroneCharacter::AThroneCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	RightHandSocketName = "Muzzle_01";
	LeftHandSocketName = "Muzzle_02";
	AttackDelayTime = 0.2f;
}

void AThroneCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AThroneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThroneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &AThroneCharacter::Move);
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &AThroneCharacter::Look);
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this, &AThroneCharacter::Attack, PrimaryProjectileClass);
	EnhancedInput->BindAction(Input_BlackholeAttack, ETriggerEvent::Triggered, this, &AThroneCharacter::Attack, BlackholeProjectileClass);
	EnhancedInput->BindAction(Input_DashAbility, ETriggerEvent::Triggered, this, &AThroneCharacter::Attack, DashProjectileClass);
}


// Input Functions

void AThroneCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MoveValue = Value.Get<FVector2D>();

	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;

	AddMovementInput(ControlRotation.Vector(), MoveValue.Y);

	const FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, MoveValue.X);
}

void AThroneCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();

	AddControllerPitchInput(LookValue.Y);
	AddControllerYawInput(LookValue.X);
}


// Basic Projectile logic (Anims, delay, etc.)

void AThroneCharacter::Attack(TSubclassOf<AThroneProjectileBase> ClassToSpawn)
{
	PlayAnimMontage(PrimaryAttackMontage);

	UNiagaraFunctionLibrary::SpawnSystemAttached(CastEffect, GetMesh(), RightHandSocketName, 
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);

	UGameplayStatics::PlaySound2D(this, CastSound);

	FTimerHandle AttackTimerHandle;
	FTimerDelegate AttackDelegate;
	AttackDelegate.BindUObject(this, &AThroneCharacter::AttackAnimTimerElapsed, ClassToSpawn);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, AttackDelegate, 1.f, false, AttackDelayTime);
}

void AThroneCharacter::AttackAnimTimerElapsed(TSubclassOf<AThroneProjectileBase> ClassToSpawn)
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation(RightHandSocketName);
	FRotator SpawnRotation = GetControlRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	AThroneProjectileBase* SpawnedProjectile = GetWorld()->SpawnActor<AThroneProjectileBase>(ClassToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
	MoveIgnoreActorAdd(SpawnedProjectile);
}