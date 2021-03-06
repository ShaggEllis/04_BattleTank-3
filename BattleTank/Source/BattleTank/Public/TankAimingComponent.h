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
	Reloading,
	OutOfAmmo
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

	EFiringStatus GetFiringStatus() const;

	UFUNCTION( BlueprintCallable, Category = "Firing" )
	int32 GetRoundsLeft() const;

protected:
	UPROPERTY( BlueprintReadOnly, Category = "State" )
	EFiringStatus FiringStatus = EFiringStatus::Locked;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;
	
	virtual void TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction ) override;

	void MoveBarrelTowards( FVector AimDirection );

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = "Firing" )
	float LaunchSpeed = 10000;

	UPROPERTY( EditDefaultsOnly, Category = "Setup" )
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY( EditDefaultsOnly, Category = "Firing" )
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

	bool IsBarrelMoving();

	FVector AimDirection;

	UPROPERTY( EditDefaultsOnly, Category = "Firing" )
	int32 RoundsLeft = 3;

};
