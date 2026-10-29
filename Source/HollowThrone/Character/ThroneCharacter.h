// Copyright - Adam Crofts

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ThroneCharacter.generated.h"

class AThroneProjectileBase;
class UNiagaraSystem;
class USoundBase;
class UAnimMontage;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;

UCLASS()
class HOLLOWTHRONE_API AThroneCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AThroneCharacter();

protected:

	// Important

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	FName RightHandSocketName;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	FName LeftHandSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TObjectPtr<UAnimMontage> PrimaryAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TObjectPtr<UNiagaraSystem> CastEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TObjectPtr<USoundBase> CastSound;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float AttackDelayTime;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AThroneProjectileBase> PrimaryProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AThroneProjectileBase> BlackholeProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AThroneProjectileBase> DashProjectileClass;


	// Components

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;


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
	void PrimaryAttack();

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_BlackholeAttack;
	void BlackholeAttack();

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_DashAbility;
	void DashAbility();


	// Modified to be re-usable across secondary (blackhole) attack and Dash.

	void Attack(TSubclassOf<AThroneProjectileBase> ClassToSpawn);
	void AttackAnimTimerElapsed(TSubclassOf<AThroneProjectileBase> ClassToSpawn);

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
