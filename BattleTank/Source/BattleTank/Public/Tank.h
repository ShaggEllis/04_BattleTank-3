// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declaration
//lass UTankAimingComponent;
//class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AimAt(FVector HitLocation);

	UFUNCTION( BlueprintCallable, Category = "Firing" )
	void Fire();

protected:
	//UPROPERTY( BlueprintReadOnly, Category = "Input" )
	//UTankAimingComponent* TankAimingComponent = nullptr;

	//UPROPERTY( BlueprintReadOnly, Category = "Input" )
	//UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY( EditDefaultsOnly, Category = "Setup" )
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY( EditDefaultsOnly, Category = "Firing" )
	float LaunchSpeed = 8000;

	UPROPERTY( EditDefaultsOnly, Category = "Firing" )
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;
};
