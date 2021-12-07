// Fill out your copyright notice in the Description page of Project Settings.


#include "CStateComponent.h"
#include "Global.h"

// Sets default values for this component's properties
UCStateComponent::UCStateComponent()
{

}


// Called when the game starts
void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UCStateComponent::ChangeType(EStateType InType)
{
	EStateType type = Type;
	Type = InType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(type, InType);


}

void UCStateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
}

void UCStateComponent::SetRollMode()
{
	ChangeType(EStateType::Roll);
}

void UCStateComponent::SetBackstepMode()
{
	ChangeType(EStateType::Backstep);
}

void UCStateComponent::SetEquipMode()
{
	ChangeType(EStateType::Equip);
}

void UCStateComponent::SetUnequipMode()
{
	ChangeType(EStateType::Unequip);
}

