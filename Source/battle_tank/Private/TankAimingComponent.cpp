// Fill out your copyright notice in the Description page of Project Settings.

#include "battle_tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTankAimingComponent::AimAt(const FVector& hitLocation, float launchSpeed) {
	if (!Barrel) {
		return;
	}
	/*
	UE_LOG(LogTemp, Warning, 
			TEXT("Aiming at Hit Location = %s, tank name=%s, barrel location=%s"), 
			*hitLocation.ToString(),
			*this->GetOwner()->GetName(),
			*this->Barrel->GetComponentLocation().ToString());*/
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectTile"));
	FVector EndLocation;
	FVector TossVelocity;
	//Calculate the OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(this,
		OutLaunchVelocity,
		StartLocation,
		hitLocation,
		launchSpeed,
		false,
		0.0,
		0.0,
		ESuggestProjVelocityTraceOption::DoNotTrace)) {
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Aiming at = %s, tankName=%s"), *AimDirection.ToString(), *GetOwner()->GetName());
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrel) {
	Barrel = barrel;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* turret) {
	Turret = turret;
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& aimDirection) {
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = aimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
//	UE_LOG(LogTemp, Warning, TEXT("Barrel rotator = %s"), *BarrelRotator.ToString());
//	UE_LOG(LogTemp, Warning, TEXT("Aiming rotator = %s"), *AimAsRotator.ToString());
//	UE_LOG(LogTemp, Warning, TEXT("Delta rotator  = %s"), *DeltaRotator.ToString());
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}