// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// if we remove these forward declaration, it compiles and run, probably because of magic UFUNCTION
class UTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick( float DeltaTime ) override;

protected:
	UFUNCTION( BlueprintImplementableEvent, Category = "Setup" )
	void FoundAimingComponent( UTankAimingComponent* AimCompRef );

private:
	UFUNCTION()
	void OnPossedTankDeath();

	void SetPawn( APawn* InPawn );

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardsCrosshair();

	UPROPERTY( EditDefaultsOnly )
	float CrosshairXLocation = 0.5f;
	
	UPROPERTY( EditDefaultsOnly )
	float CrosshairYLocation = 0.33333f;

	UPROPERTY( EditDefaultsOnly )
	float LineTraceRange = 1000000.f;

	// rturn an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation( FVector& OutHitLocation ) const;
	
	bool GetLookDirection( FVector2D ScreenLocation, FVector& LookDirection ) const;

	bool GetLookVectorHitLocation( FVector LookDirection, FVector& OutHitLocation ) const;

	UTankAimingComponent* TankAimingComponent;

};
