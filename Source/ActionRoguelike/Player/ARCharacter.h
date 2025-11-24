// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARCharacter.generated.h"

class AARProjectile;
class ARogueProjectileMagic;
struct FInputActionInstance;
struct FInputActionValue;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UNiagaraSystem;
class UARActionSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API AARCharacter : public ACharacter
{
	GENERATED_BODY()

	

protected:

	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TSubclassOf<AARProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<UNiagaraSystem> CastingEffect;

	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<USoundBase> CastingSound;
	
	UPROPERTY(VisibleAnywhere, Category = "PrimaryAttack")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Death")
	TObjectPtr<UAnimMontage> DeathMontage;


	UPROPERTY(EditDefaultsOnly, Category = "SecondaryAttack")
	TSubclassOf<AARProjectile> SecondaryProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	TSubclassOf<AARProjectile> TeleportProjectileClass;

	
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Move;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Look;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_SecondaryAttack;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Teleport;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Jump;

	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UARActionSystemComponent> ActionSystemComponent;


	void Move(const FInputActionValue& InValue);
	void Look(const FInputActionInstance& InValue);
	void PrimaryAttack();
	void AttackTimerElapsed(TSubclassOf<AARProjectile> ProjectileClassToSpawn);

	void SecondaryAttack();

	void Teleport();

	UFUNCTION()
	void OnHealthChanged(float NewHealth, float OldHealth);


public:	

	AARCharacter();

	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Damage interface from Actor
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

};
