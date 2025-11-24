// Fill out your copyright notice in the Description page of Project Settings.


#include "ARCharacter.h"

#include "Projectiles/RogueProjectileMagic.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ActionSystem/ARActionSystemComponent.h"
#include "Gameframework/CharacterMovementComponent.h"

// Sets default values
AARCharacter::AARCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	MuzzleSocketName = "Muzzle_01";

	ActionSystemComponent = CreateDefaultSubobject<UARActionSystemComponent>(TEXT("ActionSystemComponent"));
}

void AARCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ActionSystemComponent->OnHealthChanged.AddDynamic(this, &AARCharacter::OnHealthChanged);
}

// Called to bind functionality to input
void AARCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &AARCharacter::Move);
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &AARCharacter::Look);
	EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this, &AARCharacter::PrimaryAttack);
	EnhancedInput->BindAction(Input_SecondaryAttack, ETriggerEvent::Triggered, this, &AARCharacter::SecondaryAttack);
	EnhancedInput->BindAction(Input_Teleport, ETriggerEvent::Triggered, this, &AARCharacter::Teleport);
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &AARCharacter::Jump);
}



void AARCharacter::Move(const FInputActionValue& InValue)
{
	FVector2D InputValue = InValue.Get<FVector2D>();

	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;

	// Forward/Back
	AddMovementInput(ControlRot.Vector(), InputValue.X);

	// Sideways
	FVector RightDirection = ControlRot.RotateVector(FVector::RightVector);
	AddMovementInput(RightDirection, InputValue.Y);
}

void AARCharacter::Look(const FInputActionInstance& InValue)
{
	FVector2D InputValue = InValue.GetValue().Get<FVector2D>();

	AddControllerPitchInput(InputValue.Y);
	AddControllerYawInput(InputValue.X);
}

void AARCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackMontage);

	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, GetMesh(), MuzzleSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);

	UGameplayStatics::PlaySound2D(this, CastingSound);
	
	FTimerHandle AttackTimerHandle;
	const float AttackDelayTime = 0.2f;
	FTimerDelegate AttackTimerDelegate;
	AttackTimerDelegate.BindUObject(this, &AARCharacter::AttackTimerElapsed, ProjectileClass);
	
	GetWorldTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, AttackDelayTime, false);
	
}

void AARCharacter::AttackTimerElapsed(TSubclassOf<AARProjectile> ProjectileClassToSpawn)
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FRotator SpawnRotation = GetControlRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* NewProjectile= GetWorld()->SpawnActor<AActor>(ProjectileClassToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

	MoveIgnoreActorAdd(NewProjectile);
}

void AARCharacter::SecondaryAttack()
{
	PlayAnimMontage(AttackMontage);
	
	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, GetMesh(), MuzzleSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);

	UGameplayStatics::PlaySound2D(this, CastingSound);
	
	FTimerHandle AttackTimerHandle;
	const float AttackDelayTime = 0.2f;
	FTimerDelegate AttackTimerDelegate;
	AttackTimerDelegate.BindUObject(this, &AARCharacter::AttackTimerElapsed, SecondaryProjectileClass);

	GetWorldTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, AttackDelayTime, false);
}

void AARCharacter::Teleport()
{
	PlayAnimMontage(AttackMontage);

	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, GetMesh(), MuzzleSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);

	UGameplayStatics::PlaySound2D(this, CastingSound);

	FTimerHandle AttackTimerHandle;
	const float AttackDelayTime = 0.2f;
	FTimerDelegate AttackTimerDelegate;
	AttackTimerDelegate.BindUObject(this, &AARCharacter::AttackTimerElapsed, TeleportProjectileClass);

	GetWorldTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, AttackDelayTime, false);
}

void AARCharacter::OnHealthChanged(float NewHealth, float OldHealth)
{
	if (FMath::IsNearlyZero(NewHealth))
	{
		DisableInput(nullptr);
		GetMovementComponent()->StopMovementImmediately();
		PlayAnimMontage(DeathMontage);
	}
}

float AARCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	ActionSystemComponent->ApplyHealthChange(-ActualDamage);

	return ActualDamage;
}

