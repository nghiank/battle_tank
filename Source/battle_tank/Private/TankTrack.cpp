// Fill out your copyright notice in the Description page of Project Settings.

#include "battle_tank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay() {
	UE_LOG(LogTemp, Warning, TEXT("BeginPLay UTankTrack"));
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & hit)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHit"));
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Hit")));
	ApplySidewayForce();
	DriveTruck();
	CurrentThrottle = 0.0f;
}

void UTankTrack::ApplySidewayForce() {
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2;

	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::DriveTruck() {
	UE_LOG(LogTemp, Warning, TEXT("CurrentThrottle: %f"), CurrentThrottle);
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//UE_LOG(LogTemp, Warning, TEXT("RootComponent name = %s"), *RootComponent->GetName());
	if (TankRoot) {
		//UE_LOG(LogTemp, Warning, TEXT("Owner name = %s"), *GetOwner()->GetName());
		//UE_LOG(LogTemp, Warning, TEXT("Tank Throttle = %f"), Throttle);
		UE_LOG(LogTemp, Warning, TEXT("Forced Applied= %s"), *ForceApplied.ToString());
		TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	}
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}
	


