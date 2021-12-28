// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CTargetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_SECOND2_API UCTargetComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	class ACharacter* OwnerCharacter;
	class ACharacter* Target;

private:
	UPROPERTY(EditAnywhere)
		float TraceRadius = 1000.0f;
	UPROPERTY(EditAnywhere)
		TEnumAsByte<EDrawDebugTrace::Type> Debug;

private:
	TArray<class ACharacter*> TraceTargets;


public:	
	// Sets default values for this component's properties
	UCTargetComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void StartTargeting();
	void EndTargeting();
	void SetTraceTargets();
	void SetTarget();

public:
	void ToggleTarget();

};
