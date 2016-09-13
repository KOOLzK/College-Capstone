// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "test3.h"
#include "test3GameMode.h"
#include "test3HUD.h"
#include "test3Character.h"

Atest3GameMode::Atest3GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = Atest3HUD::StaticClass();
}
