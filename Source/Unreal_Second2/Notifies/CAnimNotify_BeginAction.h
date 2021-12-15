// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_BeginAction.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_SECOND2_API UCAnimNotify_BeginAction : public UAnimNotify
{
	GENERATED_BODY()
	

public:
	FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};