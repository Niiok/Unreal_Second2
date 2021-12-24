// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentBeginOverlap,
												class ACharacter*, InAttacker,
												class AActor*, InAttackCauser,
												class ACharacter*, InOtherCharacter);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentEndOverlap,
												class ACharacter*, InAttacker,
												class AActor*, InAttackCauser,
												class ACharacter*, InOtherCharacter);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttachmentCollision);

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

private:
	TArray<class UShapeComponent*> ShapeComponents;

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
	
	UFUNCTION(BlueprintCallable)
		void AttachToCollision(class UShapeComponent* InComponent, FName InSocketName);

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class USceneComponent* Scene;

public:
	UPROPERTY(BlueprintAssignable)
		FAttachmentBeginOverlap OnAttachmentBeginOverlap;
	UPROPERTY(BlueprintAssignable)
		FAttachmentEndOverlap OnAttachmentEndOverlap;
	UPROPERTY(BlueprintAssignable)
		FAttachmentCollision OnAttachmentCollision;
	UPROPERTY(BlueprintAssignable)
		FAttachmentCollision OffAttachmentCollision;


private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, 
			UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex);

public:
	void OnCollision();
	void OffCollision();

};
