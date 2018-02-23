// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "Engine/StaticMeshSocket.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//No need to protect pointers as added at construction
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

	//No need to protect pointers as added at construction
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>( FName( "Movement Component" ) );
}

void ATank::AimAt( FVector HitLocation )
{
	UTankAimingComponent* TankAimingComponent = this->FindComponentByClass<UTankAimingComponent>();
	TankAimingComponent->AimAt( HitLocation, LaunchSpeed );
}

void ATank::Fire()
{
	bool isReloaded = ( FPlatformTime::Seconds() - LastFireTime ) > ReloadTimeInSeconds;
	UTankBarrel* Barrel = this->FindComponentByClass<UTankBarrel>(); //TODO to confirmed
	if ( Barrel && ProjectileBlueprint && isReloaded )
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
