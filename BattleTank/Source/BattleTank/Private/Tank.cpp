// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//auto TankName = GetName();
	//UE_LOG( LogTemp, Warning, TEXT( "%s DONKEY: Constructor Tank.cpp C++" ),*TankName )
	//No need to protect pointers as added at construction
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

	//No need to protect pointers as added at construction
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>( FName( "Movement Component" ) );
}

void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for Blueprint BeginPlay to run
						//auto TankName = GetName();
						//UE_LOG( LogTemp, Warning, TEXT( "%s DONKEY: BeginPlay Tank.cpp C++" ), *TankName )
}


float ATank::TakeDamage( float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser )
{
	//auto DamageToApply = CurrentHealth - FMath::Clamp<float>( CurrentHealth - Damage, 0, 100 );
	int32 DamagePoints = FPlatformMath::RoundToInt( DamageAmount );
	int32 DamageToApply = FMath::Clamp<float>( DamageAmount, 0, CurrentHealth );
	CurrentHealth-= DamageToApply;
	auto TankName = GetName();
	UE_LOG( LogTemp, Warning, TEXT( "DONKEY: %f DamageAmount to %s but only %i are applied" ), DamageAmount, *TankName ,DamageToApply)
	if ( CurrentHealth <= 0 )
	{
		UE_LOG( LogTemp, Warning, TEXT( "DONKEY: %s is DIED !!" ), *TankName)
	}
	return DamageToApply;
}

