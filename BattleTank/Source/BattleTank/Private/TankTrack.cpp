// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic( this, &UTankTrack::OnHit );
}

void UTankTrack::OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit )
{
	//UE_LOG( LogTemp, Warning, TEXT( "I'm hit, I'm hit!" ) )
	DriveTrack();
	ApplySidewaysForce( );
	CurrentThrottle = 0;
}

//void UTankTrack::TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction )
//{
//	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
//
//}

void UTankTrack::ApplySidewaysForce( )
{
	// Work-out the required acceleration this frame to correct
	auto SlippageSpeed = FVector::DotProduct( GetRightVector(), GetComponentVelocity() );
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways (F = m a)
	auto TankRoot = Cast<UStaticMeshComponent>( GetOwner()->GetRootComponent() );
	auto CorrectionForce = ( TankRoot->GetMass() * CorrectionAcceleration ) / 2; // Two tracks
	TankRoot->AddForce( CorrectionForce );
}

void UTankTrack::SetThrottle( float Throttle )
{
	CurrentThrottle = FMath::Clamp<float>( CurrentThrottle + Throttle, -1, 1 );
}

void UTankTrack::DriveTrack()
{
	//auto Time = GetWorld()->GetTimeSeconds();
	/*auto Name = GetName();*/
	//UE_LOG( LogTemp, Warning, TEXT( "%s throttle: %f" ), *Name, Throttle );

	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>( GetOwner()->GetRootComponent() );
	TankRoot->AddForceAtLocation( ForceApplied, ForceLocation );
}


