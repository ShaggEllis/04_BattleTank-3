// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming,
	Reloading
};

//Forward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

//Holds Barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void AimAt( FVector HitLocation );

	UFUNCTION( BlueprintCallable, Category = "Setup" )
	void Initialise( UTankBarrel* BarrelToSet, UTankTurret* TurretToSet );

	UFUNCTION( BlueprintCallable, Category = "Firing" )
	void Fire();

protected:
	UPROPERTY( BlueprintReadOnly, Category = "State" )
	EFiringStatus FiringStatus = EFiringStatus::Aiming;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();
	void MoveBarrelTowards( FVector AimDirection );

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = "Firing" )
	float LaunchSpeed = 8000;

	UPROPERTY( EditDefaultsOnly, Category = "Setup" )
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY( EditDefaultsOnly, Category = "Firing" )
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

};
