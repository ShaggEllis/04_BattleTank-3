// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if ( !ControlledTank )
	{
		UE_LOG( LogTemp, Warning, TEXT( "%s not possesing a tank" ), *(this->GetName()) )
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "%s possessing: %s" ), *( this->GetName() ),*( ControlledTank->GetName() ) )
	}

	auto PlayerTank = GetPlayerTank();
	if ( !PlayerTank )
	{
		UE_LOG( LogTemp, Warning, TEXT( "PlayerController not possesing a tank" ))
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "PlayerController possessing: %s" ), *( PlayerTank->GetName() ) )
	}

}

void ATankAIController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if ( GetPlayerTank() )
	{

		GetControlledTank()->AimAt( GetPlayerTank()->GetActorLocation());
	}

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>( GetPawn() );
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if ( PlayerPawn )
	{
		return Cast<ATank>(PlayerPawn);
	}
	return nullptr;
}

