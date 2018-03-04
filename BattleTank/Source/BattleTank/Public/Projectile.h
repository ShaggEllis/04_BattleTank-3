// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	void LaunchProjectile( float Speed );

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	UPROPERTY( VisibleAnywhere, Category = "Component" )
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY( VisibleAnywhere, Category = "Component" )
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY( VisibleAnywhere, Category = "Component" )
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY( VisibleAnywhere, Category = "Component" )
	URadialForceComponent* ExplosionForce = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = "Setup" )
	float DestroyDelay = 5.0f;

private:
	UFUNCTION()
	void OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit );

	void DestroyProjectile();
};
