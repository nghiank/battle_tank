// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 1200000;

	UTankTrack();
	void BeginPlay() override;

	float CurrentThrottle = 0;

	void ApplySidewayForce();
	void DriveTruck();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& hit);
};
