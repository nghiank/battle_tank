// Fill out your copyright notice in the Description page of Project Settings.

#include "battle_tank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	UE_LOG(LogTemp, Warning, TEXT("Aiming elevate at speed = %f"), RelativeSpeed);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	RawNewElevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
}



