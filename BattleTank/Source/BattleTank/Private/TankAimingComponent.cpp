// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

		UE_LOG( LogTemp, Warning, TEXT( "%s Aiming at %s" ), *OurTankName, *AimDirection.ToString() )
	}


}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// rotate the barrel to point to the aim
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG( LogTemp, Warning, TEXT( "DeltaRotator: %s" ), *( DeltaRotator.ToString()) )
}

void UTankAimingComponent::SetBarrelReference( UStaticMeshComponent * BarrelToSet )
{
	Barrel = BarrelToSet;
}


