// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS( meta = ( BlueprintSpawnableComponent ) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Sets a throttle between -1 and +1
	UFUNCTION( BlueprintCallable, Category = "Input" )
	void SetThrottle( float Throttle );
	
	// Max force per track, in Newtons
	UPROPERTY( EditDefaultsOnly )
	float TrackMaxDrivingForce = 400000; // Assume 40 tonne tank, and 1g accelleration

private:
		UTankTrack();
		
		virtual void TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction ) override;

		virtual void BeginPlay() override;

		UFUNCTION()
		void OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit );
};
