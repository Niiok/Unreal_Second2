// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/TimelineComponent.h"
#include "CAim.generated.h"

/**
 *
 */
UCLASS()
class UNREAL_SECOND2_API UCAim : public UObject
{
	GENERATED_BODY()


public:
	UCAim();
	void BeginPlay(class ACharacter* InCharacter);

	void OnAim();
	void OffAim();

	void Tick(float DeltaTime);

private:
	class ACharacter* OwnerCharacter;
	class UCStateComponent* State;
	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;
	class UCurveFloat* Curve;
	class ACHUD* Hud;

public:
	FORCEINLINE bool IsAvailable() { return SpringArm != NULL && Camera != NULL; }
	FORCEINLINE bool InZoom() { return bInZoom; }
private:
	bool bInZoom;
	FTimeline Timeline;
	FOnTimelineFloat TimelineFloat;

private:
	UFUNCTION()
		void Zooming(float Value);

};
