// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/StaticMeshSocket.h"

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


void ATank::Fire()
{
	bool isReloaded = ( FPlatformTime::Seconds() - LastFireTime ) > ReloadTimeInSeconds;
	UTankBarrel* Barrel = this->FindComponentByClass<UTankBarrel>(); //TODO to confirmed
	if ( !ensure( Barrel && ProjectileBlueprint ) ) { return; }
	if (isReloaded) 
	{
		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation( FName( "Projectile" ) ),
			Barrel->GetSocketRotation( FName( "Projectile" ) ) );

		Projectile->LaunchProjectile( LaunchSpeed );
		//UE_LOG( LogTemp, Warning, TEXT( "fire" ));
		LastFireTime = FPlatformTime::Seconds();
	}
}
