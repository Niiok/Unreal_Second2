// Fill out your copyright notice in the Description page of Project Settings.


#include "CMontagesComponent.h"
#include "Global.h"

// Sets default values for this component's properties
UCMontagesComponent::UCMontagesComponent()
{
}


// Called when the game starts
void UCMontagesComponent::BeginPlay()
{
	Super::BeginPlay();

	CheckNull(DataTable);

	TArray<FMontageData*> datas;
	DataTable->GetAllRows<FMontageData>("", datas);

	for (const FMontageData* data : datas)
	{
		CLog::Log(data->AnimMontage->GetPathName());
		CLog::Print(data->AnimMontage->GetPathName());
	}
	
}

