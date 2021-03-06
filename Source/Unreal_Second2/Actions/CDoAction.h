// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actions/CActionData.h"
#include "CDoAction.generated.h"

UCLASS()
class UNREAL_SECOND2_API ACDoAction : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;

UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;

protected:
	TArray<FDoActionData> Datas;

protected:
	const bool* bEquipped;
public:
	FORCEINLINE void SetEquipped(const bool* InEquipped) { bEquipped = InEquipped; }

public:	
	// Sets default values for this actor's properties
	ACDoAction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void DoAction() {}
	virtual void Begin_DoAction() {}
	virtual void End_DoAction() {}

	virtual void OnAim() {}
	virtual void OffAim() {}

public:
	FORCEINLINE void SetDatas(TArray<FDoActionData> InDatas) { Datas = InDatas; }


public:
	UFUNCTION()
		virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker,
			class AActor* InAttackCauser,
			class ACharacter* InOtherCharacter) {}
	UFUNCTION()
		virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker,
			class AActor* InAttackCauser,
			class ACharacter* InOtherCharacter) {}

	UFUNCTION()
		virtual void OnAttachmentCollision() {}
	UFUNCTION()
		virtual void OffAttachmentCollision() {}
};
