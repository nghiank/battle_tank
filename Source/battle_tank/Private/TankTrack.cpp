// Fill out your copyright notice in the Description page of Project Settings.

#include "battle_tank.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto RootComponent = GetOwner()->GetRootComponent();
	UE_LOG(LogTemp, Warning, TEXT("RootComponent name = %s"), *RootComponent->GetName());
	auto TankRoot = Cast<UPrimitiveComponent>(GetAttachParent());
	if (TankRoot) {
		UE_LOG(LogTemp, Warning, TEXT("Owner name = %s"), *TankRoot->GetName());
		UE_LOG(LogTemp, Warning, TEXT("Tank Throttle = %f"), Throttle);
		UE_LOG(LogTemp, Warning, TEXT("Forced Applied= %s"), *ForceApplied.ToString());
		TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	}
}
	


