// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_FireStorm.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_SECOND2_API ACDoAction_FireStorm : public ACDoAction
{
	GENERATED_BODY()
	
public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;
	virtual void Tick(float DeltaTime) override;


protected:
	void BeginPlay() override;

private:
	class UBoxComponent* Box;
	class UParticleSystemComponent* Attached;

private:
	UPROPERTY(EditAnywhere)
		float Time = 5.0f;
	UPROPERTY(EditAnywhere)
		float Distance = 200.0f;
	UPROPERTY(EditAnywhere)
		float Speed = 100.0f;
	UPROPERTY(EditAnywhere)
		float HittedTime = 0.25f;

private:
	float Angle = 0;
	TArray<class ACharacter*> HittedCharacter;


private:
	UFUNCTION()
		void FInish();
	UFUNCTION()
		void Hitted();

private:
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker,
		class AActor* InAttackCauser,
		class ACharacter* InOtherCharacter) override;
	
		virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker,
			class AActor* InAttackCauser,
			class ACharacter* InOtherCharacter) override;
};
