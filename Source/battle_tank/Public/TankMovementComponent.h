// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw);
	
	
	
};
