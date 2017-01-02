// Fill out your copyright notice in the Description page of Project Settings.

#include "battle_tank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* leftTrack, UTankTrack* rightTrack) {
	if (!leftTrack || !rightTrack) return;

	LeftTrack = leftTrack;
	RightTrack = rightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (Throw > 0) {
		UE_LOG(LogTemp, Warning, TEXT("move at  = %f"), Throw);
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	}
}



