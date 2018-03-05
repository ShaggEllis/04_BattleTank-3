// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h" // So we can impliment OnDeath

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	if ( !GetPawn() ) { return; }
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::SetPawn( APawn* InPawn )
{
	Super::SetPawn( InPawn );
	if ( InPawn )
	{
		auto PossessedTank = Cast<ATank>( InPawn );
		if ( !ensure( PossessedTank ) ) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDepth.AddUniqueDynamic( this, &ATankAIController::OnPossedTankDeath );
	}
}

void ATankAIController::OnPossedTankDeath()
{
	UE_LOG( LogTemp, Warning, TEXT( "DONKEY: Tank is DIED !!" ) )
	if ( !GetPawn() ) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if ( !ensure( PlayerTank && ControlledTank && TankAimingComponent ) ) { return; }
	MoveToActor( PlayerTank ,AcceptanceRadius);
	TankAimingComponent->AimAt( PlayerTank->GetActorLocation());

	if ( TankAimingComponent->GetFiringStatus() == EFiringStatus::Locked )
	{
		TankAimingComponent->Fire();
	}

}




