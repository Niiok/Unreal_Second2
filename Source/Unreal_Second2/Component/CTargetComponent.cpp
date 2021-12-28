// Fill out your copyright notice in the Description page of Project Settings.


#include "CTargetComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UCTargetComponent::UCTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCTargetComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}


// Called every frame
void UCTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCTargetComponent::StartTargeting()
{
	SetTraceTargets();
	SetTarget();
}

void UCTargetComponent::EndTargeting()
{
}

void UCTargetComponent::SetTraceTargets()
{
	FVector start = OwnerCharacter->GetActorLocation();
	FVector end = FVector(start.X, start.Y, start.Z + 1);

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(OwnerCharacter);

	TArray<FHitResult> hitResults;
	UKismetSystemLibrary::SphereTraceMultiByProfile(
		GetWorld(), start, end, TraceRadius,
		"Pawn", false, ignoreActors, Debug, hitResults, true,
		FLinearColor::Green, FLinearColor::Red, 1.0f);

	for (const FHitResult& result : hitResults)
	{
		if (result.GetActor()->GetClass() == OwnerCharacter->GetClass())
			continue;

		ACharacter* character = Cast<ACharacter>(result.GetActor());
		if (!!character)
			TraceTargets.AddUnique(character);
	}

	/*for (const ACharacter* character : TraceTargets)
	{
		CLog::Print(character->GetName());
		CLog::Log(character->GetName());
	}*/
}

void UCTargetComponent::SetTarget()
{
	float angle = -2.0f;
	ACharacter* target = NULL;

	for (ACharacter* character : TraceTargets)
	{
		FVector direction = FQuat(OwnerCharacter->GetControlRotation()).GetForwardVector();
		FVector offset = character->GetActorLocation() - OwnerCharacter->GetActorLocation();
		offset = offset.GetSafeNormal();

		float temp = direction | offset;
		if (temp < angle)
			continue;

		angle = temp;
		target = character;
	}

	CLog::Print(target->GetName());
	CLog::Log(target->GetName());
}

void UCTargetComponent::ToggleTarget()
{
	if (!!Target)
	{
		EndTargeting();
		return;
	}

	StartTargeting();
}

