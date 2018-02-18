// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate( float RelativeSpeed )
{
	RelativeSpeed = FMath::Clamp<float>( RelativeSpeed, -1, +1 );
	auto RorationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Roration = RelativeRotation.Yaw + RorationChange;
	//UE_LOG( LogTemp, Warning, TEXT( "RelativeSpeed: %f - RorationChange: %f - Roration: %f" ), RelativeSpeed, RorationChange, Roration )
	SetRelativeRotation( FRotator( 0, Roration, 0 ) );

}


