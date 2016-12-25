// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;
	
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void AimTowordsCrosshair();
	bool GetSightRayHitLocation(FVector& hitLocation) const;
	
};
