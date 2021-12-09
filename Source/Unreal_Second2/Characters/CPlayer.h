#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Component/CStateComponent.h"
#include "CPlayer.generated.h"

UCLASS()
class UNREAL_SECOND2_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;	
	
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;	
	
	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;	
	
	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;	

	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* Action;	

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);

	void OnAvoid();

	void Begin_Roll();
	void Begin_Backstep();
public:
	void End_Roll();
	void End_Backstep();

private:
	void OnOneHand();

};
