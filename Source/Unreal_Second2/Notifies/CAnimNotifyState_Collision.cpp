// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_Collision.h"
#include "Global.h"
#include "Actions/CActionData.h"
#include "Actions/CAttachment.h"
#include "Component/CActionComponent.h"



FString UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action =
		CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	ACAttachment* attachment =
		CHelpers::GetComponent<ACAttachment>(MeshComp->GetOwner());
	CheckNull(attachment);
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* action =
		CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(action);

	ACAttachment* attachment =
		CHelpers::GetComponent<ACAttachment>(MeshComp->GetOwner());
	CheckNull(attachment);
}