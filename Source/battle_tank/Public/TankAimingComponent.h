// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8 {
	Locked, 
	Aiming,
	Reloading
};

class UTankTurret;
class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void AimAt(const FVector& hitLocation,  float launchSpeed);


	void SetBarrelReference(UTankBarrel* barrel);
	void SetTurretReference(UTankTurret* turret);
	void MoveBarrelTowards(const FVector& aimDirection);
protected:
	UPROPERTY(BlueprintReadOnly, Category="Setup")
	EFiringState FiringState = EFiringState::Reloading;
private:
	UTankBarrel* Barrel;
	UTankTurret* Turret;

	
};
