// Fill out your copyright notice in the Description page of Project Settings.


#include "CActionComponent.h"
#include "Global.h"

// Sets default values for this component's properties
UCActionComponent::UCActionComponent()
{
}


// Called when the game starts
void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType prevType = Type;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())
		OnActionTypeChanged.Broadcast(prevType, InNewType);
}

void UCActionComponent::SetMode(EActionType InType)
{
	if (Type == InType)
	{
		SetUnarmedMode();
		return;
	}
	else if (IsUnarmedMode() == false)
	{
		// unequip
	}

	// equip

	ChangeType(InType);
}

void UCActionComponent::SetUnarmedMode()
{
	SetMode(EActionType::Unarmed);
}

void UCActionComponent::SetOneHandMode()
{
	SetMode(EActionType::OneHand);
}

void UCActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);
}
