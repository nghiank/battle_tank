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
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnLeft(float Throw) {
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	//UE_LOG(LogTemp, Warning, TEXT("Throw:%f"), Throw);
}


void UTankMovementComponent::RequestDirectMove(const FVector& velocity, bool bForceMaxSpeed) {
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = velocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow * 1.2);

	//auto v = TankForward;
	auto k = AIForwardIntention;

	auto StartLocation = GetOwner()->GetActorLocation();
	auto EndLocation = GetOwner()->GetActorLocation() + k * 1000;
	//UE_LOG(LogTemp, Warning, TEXT("GetOwnerLocation=%s, EndLocation:%s"), *StartLocation.ToString(), *EndLocation.ToString());
	DrawDebugLine(
		GetWorld(),
		StartLocation,
		EndLocation,
		FColor(255, 19, 0),
		false, -1, 0,
		12.333
	);

	
	auto Throw = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(Throw * 1.3);
	//UE_LOG(LogTemp, Warning, TEXT("Name=%s, Throw:%f, FordWard:%f"), *GetOwner()->GetName(), Throw, ForwardThrow);
}
