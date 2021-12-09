// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle,
	Roll,
	Backstep,
	Equip,
	Unequip,
	EnumMax
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateType, InPrevType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_SECOND2_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	EStateType Type = EStateType::Idle;

public:	
	// Sets default values for this component's properties
	UCStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsIdleMode() { return Type == EStateType::Idle; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsRollMode() { return Type == EStateType::Roll; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsBackstepMode() { return Type == EStateType::Backstep; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsEquipMode() { return Type == EStateType::Equip; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnequipMode() { return Type == EStateType::Unequip; }

public:
	UPROPERTY(BlueprintAssignable)
		FStateTypeChanged OnStateTypeChanged;
private:
	void ChangeType(EStateType InType);

public:
	void SetIdleMode();
	void SetRollMode();
	void SetBackstepMode();

	void SetEquipMode();
	void SetUnequipMode();
};
