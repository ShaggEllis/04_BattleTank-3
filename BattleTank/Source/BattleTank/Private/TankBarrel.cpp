// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate( float RelativeSpeed )
{
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG( LogTemp, Warning, TEXT( "%f: Barel->Elevate() called at speed %f" ),Time, RelativeSpeed )

	// Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame time

	RelativeSpeed = FMath::Clamp<float>( RelativeSpeed, -1, +1 );
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>( RawNewElevation, MinElevationDegrees, MaxElevationDegrees );
	//UE_LOG( LogTemp, Warning, TEXT( "ElevationChange: %f - Elevation: %f" ), ElevationChange, RawNewElevation )
	SetRelativeRotation( FRotator( Elevation, 0, 0 ) );

}


