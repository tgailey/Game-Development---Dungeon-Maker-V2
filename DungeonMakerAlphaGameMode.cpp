// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DungeonMakerAlphaGameMode.h"
#include "DungeonMakerAlphaHUD.h"
#include "DungeonMakerAlphaCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MasterController.h"

ADungeonMakerAlphaGameMode::ADungeonMakerAlphaGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
//	DefaultPawnClass = PlayerPawnClassFinder.Class;
	DefaultPawnClass = NULL;
	//static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("/Script/DungeonMakerAlpha.MasterController'"));
	PlayerControllerClass = AMasterController::StaticClass();


	// use our custom HUD class
	HUDClass = ADungeonMakerAlphaHUD::StaticClass();
}
