// Fill out your copyright notice in the Description page of Project Settings.


#include "CThrow.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ACThrow::ACThrow()
{
	PrimaryActorTick.bCanEverTick = false;

	CHelpers::CreateComponent<USphereComponent>(this, &Sphere, "Sphere");
	RootComponent = Sphere;
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Particle, "Particle", Sphere);
	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &Projectile, "Projectile");

	InitialLifeSpan = 3.0f;

	Projectile->InitialSpeed = 4000.0f;
	Projectile->MaxSpeed = 8000.0f;
	Projectile->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void ACThrow::BeginPlay()
{
	Super::BeginPlay();

	TArray<USphereComponent*> components;
	GetComponents<USphereComponent>(components);

	for (UShapeComponent* component : components)
	{
		component->OnComponentBeginOverlap.AddDynamic(this, &ACThrow::OnComponentBeginOverlap);
	}
}

void ACThrow::OnComponentBeginOverlap(
	UPrimitiveComponent * OverlappedComponent,
	AActor * OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult & SweepResult)
{
	if (!!Explosion)
	{
		FTransform transform = ExplosionTransform;
		transform.AddToTranslation(SweepResult.Location);
		transform.SetRotation(FQuat(SweepResult.ImpactNormal.Rotation()));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, transform);
	}

	if (OnThrowBeginOverlap.IsBound())
	{
		OnThrowBeginOverlap.Broadcast(SweepResult);
	}
	
	Destroy();
}
