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
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::IntendTurnLeft(float Throw) {
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}


