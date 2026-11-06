// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ThroneCharacter.generated.h"

struct FGameplayTag;
class AThroneProjectileBase;
class UNiagaraSystem;
class USoundBase;
class UAnimMontage;
class USpringArmComponent;
class UCameraComponent;
class UThroneAbilitySystemComponent;
class UInputAction;

UCLASS()
class HOLLOWTHRONE_API AThroneCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AThroneCharacter();

protected:
	// Animations

	UPROPERTY(EditDefaultsOnly, Category = "Death")
	TObjectPtr<UAnimMontage> DeathMontage;


	
	// Components

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;


	// Ability System

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UThroneAbilitySystemComponent> AbilitySystemComponent;


	// Input

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Move;
	void Move(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Look;
	void Look(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_BlackholeAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_DashAbility;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Sprint;


	// Modified to be re-usable across secondary (blackhole) attack and Dash.

	void StartAbility(FGameplayTag InAbilityName);

	void StopAbility(FGameplayTag InAbilityName);

	UFUNCTION()
	void OnHealthChanged(float OldHealth, float NewHealth);


public:	

	virtual void PostInitializeComponents() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


};
