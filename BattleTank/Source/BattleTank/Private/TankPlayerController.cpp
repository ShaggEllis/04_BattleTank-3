// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if ( !ensure( TankAimingComponent ) ) { return; }
	FoundAimingComponent( TankAimingComponent );
}

// Called every frame
void ATankPlayerController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}
 
void ATankPlayerController::AimTowardsCrosshair()
{
	auto TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if ( !ensure( TankAimingComponent ) ) { return; }

	FVector OutHitLocation;
	// If it hits the landscape
	if ( GetSightRayHitLocation( OutHitLocation ) )
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
		GetLookVectorHitLocation( LookDirection , HitLocation );
	}

	// Line-trace along that LookDirection, and see what we hit (up to max range)
	return true;
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
