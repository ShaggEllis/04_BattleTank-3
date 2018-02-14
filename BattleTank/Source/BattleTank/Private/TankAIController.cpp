// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if ( !ControlledTank )
	{
		UE_LOG( LogTemp, Warning, TEXT( "%s not possesing a tank" ), *(this->GetName()) );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "%s possessing: %s" ), *( this->GetName() ),*( ControlledTank->GetName() ) );
	}

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>( GetPawn() );
}

