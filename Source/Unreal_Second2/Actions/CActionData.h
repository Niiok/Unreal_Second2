// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"

USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;
	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;
	UPROPERTY(EditAnywhere)
		FName StartSection;
	UPROPERTY(EditAnywhere)
		bool bCanMove = true;
	UPROPERTY(EditAnywhere)
		bool bPawnControl = true;
};

USTRUCT(BlueprintType)
struct FDoActionData : public FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Power = 5.0f;

	UPROPERTY(EditAnywhere)
		float HitStop;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* Effect;

	UPROPERTY(EditAnywhere)
		FTransform EffectTransform;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShake> ShakeClass;
};

/**
 *
 */
UCLASS()
class UNREAL_SECOND2_API UCActionData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACEquipment> EquipmentClass;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACAttachment> AttachmentClass;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FEquipmentData EquipmentData;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACDoAction> DoActionClass;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FDoActionData> DoActionDatas;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FLinearColor EquipmentColor;

private:
	class ACEquipment* Equipment;
	class ACAttachment* Attachment;
	class ACDoAction* DoAction;


public:
	void BeginPlay(class ACharacter* InOwnerCharacter);

public:
	FORCEINLINE class ACEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE class ACDoAction* GetDoAction() { return DoAction; }
	FORCEINLINE class ACAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE FLinearColor GetEquipmentColor() { return EquipmentColor; }

	FString GetLabelName(class ACharacter* InOwnerCharacterm, FString InName);

};
