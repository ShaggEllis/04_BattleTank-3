// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	//No need to protect pointers as added at construction
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>( FName( "Projectile Movement Component" ) );
	ProjectileMovementComponent->bAutoActivate = false;
	
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>( FName( "CollisionMesh" ) );
	SetRootComponent( CollisionMesh );
	CollisionMesh->SetNotifyRigidBodyCollision( true );
	CollisionMesh->SetVisibility( false );

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>( FName( "LaunchBlast" ) );
	LaunchBlast->SetupAttachment( RootComponent ); //TODO check if needed

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>( FName( "ImpactBlast" ) );
	ImpactBlast->SetupAttachment( RootComponent ); 
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>( FName( "ExplosionForce" ) );
	ExplosionForce->SetupAttachment( RootComponent ); 
	//ExplosionForce->bAutoActivate = false;

}

void AProjectile::OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit )
{
	//UE_LOG( LogTemp, Warning, TEXT( "I'm hit, I'm hit!" ) )
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic( this, &AProjectile::OnHit );
	
}

void AProjectile::LaunchProjectile( float Speed )
{
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG( LogTemp, Warning, TEXT( "%f: Projectile fires at %f" ), Time, Speed );
	ProjectileMovementComponent->SetVelocityInLocalSpace( FVector::ForwardVector * Speed );
	ProjectileMovementComponent->Activate();
}

