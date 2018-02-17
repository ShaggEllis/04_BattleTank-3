// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate( float RelativeSpeed )
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG( LogTemp, Warning, TEXT( "%f: Barel->Elevate() called at speed %f" ),Time, RelativeSpeed )
}


