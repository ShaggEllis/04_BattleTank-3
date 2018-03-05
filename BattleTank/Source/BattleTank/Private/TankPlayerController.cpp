// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h" // So we can impliment OnDeath

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if( !GetPawn() ) { return; }
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if ( !ensure( TankAimingComponent ) ) { return; }
	FoundAimingComponent( TankAimingComponent );
}


void ATankPlayerController::SetPawn( APawn* InPawn )
{
	Super::SetPawn( InPawn );
	if ( InPawn )
	{
		auto PossessedTank = Cast<ATank>( InPawn );
		if ( !ensure( PossessedTank ) ) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDepth.AddUniqueDynamic( this, &ATankPlayerController::OnPossedTankDeath );
	}
}

void ATankPlayerController::OnPossedTankDeath()
{
	UE_LOG( LogTemp, Warning, TEXT( "DONKEY: PlayerTank is DIED !!" ) )
	StartSpectatingOnly();
}


// Called every frame
void ATankPlayerController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}
 
void ATankPlayerController::AimTowardsCrosshair()
{
	if ( !GetPawn() ) { return; }
	FVector OutHitLocation;
	// If it hits the landscape
	bool bGotHitLocation = GetSightRayHitLocation( OutHitLocation );
	//UE_LOG( LogTemp, Warning, TEXT( "bGotHitLocation: %i" ), bGotHitLocation );
	if ( bGotHitLocation )
	{
		TankAimingComponent->AimAt( OutHitLocation );
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation( FVector& HitLocation ) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize( ViewportSizeX, ViewportSizeY );
	auto ScreenLocation = FVector2D( ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation );

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if ( GetLookDirection( ScreenLocation, LookDirection ) )
	{
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		return GetLookVectorHitLocation( LookDirection , HitLocation );
	}
	return false;
}

bool ATankPlayerController::GetLookDirection( FVector2D ScreenLocation, FVector& LookDirection ) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation( FVector LookDirection, FVector & OutHitLocation ) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	))
	{
		//OutHitLocation = HitResult.ImpactPoint;
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector( 0.f );
	return false;

}
