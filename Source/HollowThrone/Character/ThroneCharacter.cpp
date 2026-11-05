// Copyright - Adam Crofts


#include "ThroneCharacter.h"
#include "Projectile/ThroneProjectileBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystem/ThroneAbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "Engine.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/PawnMovementComponent.h"
#include "ThroneGameTypes.h"

AThroneCharacter::AThroneCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	AbilitySystemComponent = CreateDefaultSubobject<UThroneAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	
}

void AThroneCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	AbilitySystemComponent->OnHealthChanged.AddDynamic(this, &AThroneCharacter::OnHealthChanged);
}

void AThroneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// Bind movement and look input actions

	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &AThroneCharacter::Move);
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &AThroneCharacter::Look);
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ACharacter::Jump);

	// Bind abilities to input actions

	EnhancedInput->BindAction(Input_Sprint, ETriggerEvent::Started, this,
		&AThroneCharacter::StartAbility, FName("Sprint"));
	EnhancedInput->BindAction(Input_Sprint, ETriggerEvent::Completed, this,
		&AThroneCharacter::StopAbility, FName("Sprint"));

	EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this, 
		&AThroneCharacter::StartAbility, FName("PrimaryAttack"));
	EnhancedInput->BindAction(Input_BlackholeAttack, ETriggerEvent::Triggered, this, 
		&AThroneCharacter::StartAbility, FName("BlackholeAttack"));
	EnhancedInput->BindAction(Input_DashAbility, ETriggerEvent::Triggered, this, 
		&AThroneCharacter::StartAbility, FName("Teleport"));
}

float AThroneCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	AbilitySystemComponent->ApplyHealthChange(-ActualDamage);
	return ActualDamage;
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


void AThroneCharacter::StartAbility(FName InAbilityName)
{
	AbilitySystemComponent->StartAbility(InAbilityName);
}

void AThroneCharacter::StopAbility(FName InAbilityName)
{
	AbilitySystemComponent->StopAbility(InAbilityName);
}


void AThroneCharacter::OnHealthChanged(float OldHealth, float NewHealth)
{
	if (NewHealth <= 0.f)
	{
		DisableInput(nullptr);
		GetMovementComponent()->StopMovementImmediately();
		PlayAnimMontage(DeathMontage);
	}
}