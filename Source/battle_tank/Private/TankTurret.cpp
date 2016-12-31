// Fill out your copyright notice in the Description page of Project Settings.

#include "battle_tank.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float delta) {
	delta = FMath::Clamp<float>(delta, -1.0, 1.0);
	auto degreeChange = delta * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto newDegree = RelativeRotation.Yaw + degreeChange;
	SetRelativeRotation(FRotator(0.0, newDegree, 0.0));

}



