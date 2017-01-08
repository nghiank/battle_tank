// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

UCLASS()
class BATTLE_TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void AimTowordsCrosshair();
	bool GetSightRayHitLocation(FVector& hitLocation) const;
	UPROPERTY(EditAnyWhere)
		float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnyWhere)
		float CrosshairYLocation = 0.33;
	bool GetLookDirection(const FVector2D& screenLocation, FVector& lookDirection) const;
	bool GetLookVectorHitLocation(const FVector& lookDirection, FVector& hitLocationl) const;
	UPROPERTY(EditAnyWhere)
	float LineTraceRange = 1000000;

};
