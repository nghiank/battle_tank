// Fill out your copyright notice in the Description page of Project Settings.

#include "battle_tank.h"

#include "TankPlayerController.h"
#include "TankAIController.h"


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto controlledTank = GetPlayerTank();
	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI controller GetControlledPawn return NULL"));;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI control Pawn %s"), *controlledTank->GetName());;
	}
}

ATank*  ATankAIController::GetPlayerTank() const {
	auto playerController = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!playerController) {
		UE_LOG(LogTemp, Warning, TEXT("Not able to get FirstPlayerController"));
		return NULL;
	}

	ATank* tank = playerController->GetControlledTank();
	if (!tank) {
		UE_LOG(LogTemp, Warning, TEXT("Not able to get Tank"));
		return NULL;
	}
	UE_LOG(LogTemp, Warning, TEXT("Tank Got!!"));

	return tank;
}

