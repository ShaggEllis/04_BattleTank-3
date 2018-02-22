// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise( UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet )
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward( float Throw )
{
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG( LogTemp, Warning, TEXT( "Intend move forward throw: %f" ), Throw );
	if ( !LeftTrack || !RightTrack ) { return; }
	LeftTrack->SetThrottle( Throw );
	RightTrack->SetThrottle( Throw );
}

void UTankMovementComponent::IntendTurnRight( float Throw )
{
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG( LogTemp, Warning, TEXT( "Intend move forward throw: %f" ), Throw );
	if ( !LeftTrack || !RightTrack ) { return; }
	LeftTrack->SetThrottle( Throw );
	RightTrack->SetThrottle( -Throw );
}

void UTankMovementComponent::RequestDirectMove( const FVector & MoveVelocity, bool bForceMaxSpeed )
{
	UE_LOG( LogTemp, Warning, TEXT( "%s RequestDirectMove %s" ), *GetOwner()->GetName(), *MoveVelocity.GetSafeNormal().ToString() );
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	float Throw = FVector::DotProduct( TankForward, AIForwardIntention );
	IntendMoveForward( Throw );
}


