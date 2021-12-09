// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

UCLASS()
class UNREAL_SECOND2_API ACAttachment : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;
	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;
	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;

public:	
	// Sets default values for this actor's properties
	ACAttachment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnEquip();
	UFUNCTION(BlueprintImplementableEvent)
		void OnUnequip();

protected:
	UFUNCTION(BlueprintCallable)
		void AttachToActor(FName InSocketName);

};
