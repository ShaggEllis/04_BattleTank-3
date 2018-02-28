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
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UTankAimingComponent::BeginPlay()
{
		// So that first first is after initial reload
		LastFireTime = FPlatformTime::Seconds();
}

	// ...
void UTankAimingComponent::TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction )
 {
	if ( ( FPlatformTime::Seconds() - LastFireTime ) < ReloadTimeInSeconds )
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if ( IsBarrelMoving() )
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
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
	//UE_LOG( LogTemp, Warning, TEXT( "DeltaRotator.Pitch: %f" ), DeltaRotator.Pitch )
	//UE_LOG( LogTemp, Warning, TEXT( "BarrelRotator: %s" ), *BarrelRotator.ToString() )
	//UE_LOG( LogTemp, Warning, TEXT( "AimAsRotator: %s" ), *AimAsRotator.ToString() )
	//UE_LOG( LogTemp, Warning, TEXT( "DeltaRotator: %s" ), *DeltaRotator.ToString() )
	Barrel->Elevate( DeltaRotator.Pitch );
	// My solution
	//if ( DeltaRotator.Yaw > 180 )
	//{
	//	DeltaRotator.Yaw = DeltaRotator.Yaw - 360;
	//}
	//if ( DeltaRotator.Yaw < -180 )
	//{
	//	DeltaRotator.Yaw = DeltaRotator.Yaw + 360;
	//}
	// Ben's Solution
	if ( FMath::Abs(DeltaRotator.Yaw) < 180 )
	{
		Turret->Rotate( DeltaRotator.Yaw );
	}
	else
	{
		Turret->Rotate( -DeltaRotator.Yaw );
	}

	//UE_LOG( LogTemp, Warning, TEXT( "DeltaRotator: %f" ), DeltaRotator.Pitch )
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if ( !ensure( Barrel ) ) { return false; }
	auto BarrelCurrentForwardVector = Barrel->GetForwardVector();
	return ( !BarrelCurrentForwardVector.Equals( AimDirection, 0.03 ) );
}

void UTankAimingComponent::Fire()
{
	if ( FiringStatus != EFiringStatus::Reloading )
	{
		if ( !ensure( Barrel && ProjectileBlueprint ) ) { return; }
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


