// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeadRainGameMode.h"
#include "DeadRainCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADeadRainGameMode::ADeadRainGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
