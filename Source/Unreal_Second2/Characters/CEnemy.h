// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/ICharacter.h"
#include "CEnemy.generated.h"

UCLASS()
class UNREAL_SECOND2_API ACEnemy : public ACharacter, public IICharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

	// IICharacter을(를) 통해 상속됨
	virtual void ChangeColor(FLinearColor InColor);

};
