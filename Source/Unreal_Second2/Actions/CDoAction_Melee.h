// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Melee.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_SECOND2_API ACDoAction_Melee : public ACDoAction
{
	GENERATED_BODY()
	
public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

private:
	bool bExist;
	bool bEnable;
	bool bLast;
	int32 Index;

public:
	FORCEINLINE void EnableCombo() { bEnable = true; }
	FORCEINLINE void DisableCombo() { bEnable = false; }

	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker,
		class AActor* InAttackCauser,
		class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker,
		class AActor* InAttackCauser,
		class ACharacter* InOtherCharacter) override;

};
