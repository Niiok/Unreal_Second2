// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actions/CActionData.h"
#include "CEquipment.generated.h"

UCLASS()
class UNREAL_SECOND2_API ACEquipment : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;
	
	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;

private:
	FEquipmentData Data;

public:	
	// Sets default values for this actor's properties
	ACEquipment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintNativeEvent)
		void Equip();
	void Equip_Implemention();

	UFUNCTION(BlueprintNativeEvent)
		void Begin_Equip();
	void Begin_Equip_Implemetion();
	
	UFUNCTION(BlueprintNativeEvent)
		void End_Equip();
	void End_Equip_Implemetion();
	

	UFUNCTION(BlueprintNativeEvent)
		void Unequip();
	void Unequip_Implemetion();



public:
	FORCEINLINE void SetData(FEquipmentData data) 
	{}

};
