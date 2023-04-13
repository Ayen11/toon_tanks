// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile2.h"

#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile2::AProjectile2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1400.f;
	ProjectileMovementComponent->InitialSpeed = 1400.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void AProjectile2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

