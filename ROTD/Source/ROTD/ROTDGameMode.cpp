// Copyright Epic Games, Inc. All Rights Reserved.

#include "ROTDGameMode.h"
#include "ROTDCharacter.h"
#include "UObject/ConstructorHelpers.h"

AROTDGameMode::AROTDGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
