// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

void UTankAimingComponent::Initialise( UTankBarrel* BarrelToSet, UTankTurret* TurretToSet )
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt( FVector HitLocation)
{
	if ( !ensure(Barrel )) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation( FName( "Projectile" ) );
	//TArray < AActor * > ActorsToIgnore;
	//bool bHaveAImSolution = UGameplayStatics::SuggestProjectileVelocity(
	//	this,
	//	OutLaunchVelocity,
	//	StartLocation,
	//	HitLocation,
	//	LaunchSpeed,
	//	false,
	//	0,
	//	0,
	//	ESuggestProjVelocityTraceOption::DoNotTrace,
	//	FCollisionResponseParams(),
	//	ActorsToIgnore,
	//	true );
	bool bHaveAImSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace);
	if( bHaveAImSolution )
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards( AimDirection );
		
		//auto OurTankName = GetOwner()->GetName();
		//auto BarrelLocation = Barrel->GetComponentLocation();
		//UE_LOG( LogTemp, Warning, TEXT( "%s aiming at %s from %s" ), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString() )
		//UE_LOG( LogTemp, Warning, TEXT( "Firing at %f" ), LaunchSpeed )
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG( LogTemp, Warning, TEXT( "%f: %s Aiming at %s" ), Time, *OurTankName, *AimDirection.ToString() )
		//UE_LOG( LogTemp, Warning, TEXT( "%f: Aim solution found" ), Time );
	}
	else
	{
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG( LogTemp, Warning, TEXT( "%f: No aim solve found" ), Time );
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if ( !ensure(Barrel) || !ensure( Turret )) { return; }
	auto AimAsRotator = AimDirection.Rotation();
	// rotate the barrel to point to the aim
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG( LogTemp, Warning, TEXT( "DeltaRotator: %f" ), DeltaRotator.Pitch )
	Barrel->Elevate( DeltaRotator.Pitch );
	Turret->Rotate( DeltaRotator.Yaw );

	//UE_LOG( LogTemp, Warning, TEXT( "DeltaRotator: %f" ), DeltaRotator.Pitch )
}

void UTankAimingComponent::Fire()
{
	bool isReloaded = ( FPlatformTime::Seconds() - LastFireTime ) > ReloadTimeInSeconds;
	if ( !ensure( Barrel && ProjectileBlueprint ) ) { return; }
	if ( isReloaded )
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
