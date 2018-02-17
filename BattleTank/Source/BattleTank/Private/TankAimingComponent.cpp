// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::AimAt( FVector HitLocation, float LaunchSpeed )
{
	if ( !Barrel ) { return; }
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
		
		auto OurTankName = GetOwner()->GetName();
		//auto BarrelLocation = Barrel->GetComponentLocation();
		//UE_LOG( LogTemp, Warning, TEXT( "%s aiming at %s from %s" ), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString() )
		//UE_LOG( LogTemp, Warning, TEXT( "Firing at %f" ), LaunchSpeed )
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG( LogTemp, Warning, TEXT( "%f: %s Aiming at %s" ), Time, *OurTankName, *AimDirection.ToString() )
		UE_LOG( LogTemp, Warning, TEXT( "%f: Aim solution found" ), Time );
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG( LogTemp, Warning, TEXT( "%f: No aim solve found" ), Time );
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// rotate the barrel to point to the aim
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG( LogTemp, Warning, TEXT( "DeltaRotator: %f" ), DeltaRotator.Pitch )

	Barrel->Elevate( DeltaRotator.Pitch ); //TODO remove magic number


}

void UTankAimingComponent::SetBarrelReference( UTankBarrel * BarrelToSet )
{
	Barrel = BarrelToSet;
}


