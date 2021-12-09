// Fill out your copyright notice in the Description page of Project Settings.


#include "CAttachment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CStatusComponent.h"

// Sets default values
ACAttachment::ACAttachment()
{
}

// Called when the game starts or when spawned
void ACAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);

	Super::BeginPlay();
	
}

void ACAttachment::AttachToActor(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);	
}

