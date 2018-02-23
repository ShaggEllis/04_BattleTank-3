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

//Holds Barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt( FVector HitLocation, float LaucnSpeed );

	void SetBarrelReference(  UTankBarrel* BarrelToSet );

	void SetTurretReference( UTankTurret* TurretToSet );

protected:
	UPROPERTY( BlueprintReadOnly, Category = "State" )
	EFiringStatus FiringStatus = EFiringStatus::Aiming;

private:
	 UTankBarrel* Barrel = nullptr;

	 UTankTurret* Turret = nullptr;

	void MoveBarrelTowards( FVector AimDirection );
};
