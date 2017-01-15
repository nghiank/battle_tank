// Fill out your copyright notice in the Description page of Project Settings.

#include "battle_tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(const FVector& hitLocation) {
	TankAimingComponent->AimAt(hitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* barrel) {
	TankAimingComponent->SetBarrelReference(barrel);
	Barrel = barrel;
}
void ATank::SetTurretReference(UTankTurret* turret) {
	TankAimingComponent->SetTurretReference(turret);
}

void ATank::Fire() {
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds;
	if (!isReloaded) {
		return;
	}

	auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("Tank Fire at %f"), Time);
	if (!Barrel) return;
	FVector Location = Barrel->GetSocketLocation(FName("ProjectTile"));
	FRotator Rotator = Barrel->GetSocketRotation(FName("ProjectTile"));
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotator);
	Projectile->LaunchProjectile(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
}

float ATank::TakeDamage(
	float DamageAmount,
	struct FDamageEvent const & DamageEvent,
	class AController * EventInstigator,
	AActor * DamageCauser) {
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	auto DamageToApply = FMath::Clamp<int32>(DamageAmount, 0, DamagePoints);
	UE_LOG(LogTemp, Warning, TEXT("Tank GotDamage = %i"), DamageToApply);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("Tank Die"));
	}

	return 1.0f;
}

float ATank::GetHealthPercent() {
	return (float)CurrentHealth / (float)StartingHealth;
}
