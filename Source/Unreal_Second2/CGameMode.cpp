// Copyright Epic Games, Inc. All Rights Reserved.


#include "CGameMode.h"
#include "Global.h"
#include "GameFramework/HUD.h"

ACGameMode::ACGameMode()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, 
		TEXT("Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'"));

	CHelpers::GetClass<AHUD>(&HUDClass,
		TEXT("Blueprint'/Game/BP_CHUD.BP_CHUD_C'"));


}