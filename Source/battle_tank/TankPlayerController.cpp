// Fill out your copyright notice in the Description page of Project Settings.

#include "battle_tank.h"
#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();
	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player controller GetControlledPawn return NULL"));;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player control Pawn %s"), *controlledTank->GetName());;
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("Player control Tick %f"), DeltaTime);
	AimTowordsCrosshair();
}

void ATankPlayerController::AimTowordsCrosshair() {
	if (!GetControlledTank()) {
		UE_LOG(LogTemp, Warning, TEXT("Not able to find controlled tank"));
		return;
	}

	FVector HitLocation;
	UE_LOG(LogTemp, Warning, TEXT("HitLocation=%s"),*HitLocation.ToString());
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const {
	return true;
}

