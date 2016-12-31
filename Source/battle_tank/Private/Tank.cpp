// Fill out your copyright notice in the Description page of Project Settings.

#include "battle_tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
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
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("Tank Fire at %f"), Time);
	if (!Barrel) return;
	FVector Location = Barrel->GetSocketLocation(FName("ProjectTile"));
	GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, FRotator::ZeroRotator);
}