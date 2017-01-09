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

	auto AimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent) {
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController - not able to find AimingComponent"));
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);	
	AimTowordsCrosshair();
}

void ATankPlayerController::AimTowordsCrosshair() {
	if (!GetControlledTank()) {
		UE_LOG(LogTemp, Warning, TEXT("Not able to find controlled tank"));
		return;
	}

	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation)) {
		GetControlledTank()->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const {
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector WorldDirection;
	if (GetLookDirection(ScreenLocation, WorldDirection)) {
		//UE_LOG(LogTemp, Warning, TEXT("world direction=%s"), *WorldDirection.ToString());
		if (GetLookVectorHitLocation(WorldDirection, hitLocation)) {
			return true;
		}
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(const FVector2D& screenLocation, FVector& lookDirection) const{
	FVector WorldLocation;
	DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, WorldLocation, lookDirection);
	return true;
}
bool ATankPlayerController::GetLookVectorHitLocation(const FVector& lookDirection, FVector& hitLocation) const{
	FHitResult OutHit;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	//UE_LOG(LogTemp, Warning, TEXT("Look direction:%s"), *lookDirection.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Starting Location:%s"), *StartLocation.ToString());
	auto EndLocation = StartLocation + lookDirection * LineTraceRange;
	//UE_LOG(LogTemp, Warning, TEXT("End Location:%s"), *EndLocation.ToString());
	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {
		hitLocation = OutHit.Location;
		return true;
	}
	return false;
}

