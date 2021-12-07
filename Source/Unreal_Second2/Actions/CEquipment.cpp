// Fill out your copyright notice in the Description page of Project Settings.


#include "CEquipment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"
#include "Component/CStatusComponent.h"


// Sets default values
ACEquipment::ACEquipment()
{

}

// Called when the game starts or when spawned
void ACEquipment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	State = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);

	Super::BeginPlay();
	
}

void ACEquipment::Equip_Implemention()
{
}

void ACEquipment::Begin_Equip_Implemetion()
{
}

void ACEquipment::End_Equip_Implemetion()
{
}

void ACEquipment::Unequip_Implemetion()
{
}
