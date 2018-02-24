// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	if ( !GetPawn() ) { return; }
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if ( !ensure( PlayerTank && ControlledTank && TankAimingComponent ) ) { return; }
	MoveToActor( PlayerTank ,AcceptanceRadius);
	TankAimingComponent->AimAt( PlayerTank->GetActorLocation());
	//TODO remove comment
	//TankAimingComponent->Fire();
}


