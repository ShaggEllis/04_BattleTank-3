// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Return current health as a percentage of starting health, between 0 and 1
	UFUNCTION( BlueprintPure, Category = "Health" )
	float GetHealthPercent() const;

protected:
	virtual float TakeDamage( float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser )  override;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY( EditDefaultsOnly, Category = "Setup" )
	int32 StartingHealth = 100.0f;

	UPROPERTY( VisibleAnywhere, Category = "Health" )
	int32 CurrentHealth= StartingHealth;


};
