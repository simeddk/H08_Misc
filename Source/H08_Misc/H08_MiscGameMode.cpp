// Copyright Epic Games, Inc. All Rights Reserved.

#include "H08_MiscGameMode.h"
#include "H08_MiscPlayerController.h"
#include "H08_MiscCharacter.h"
#include "UObject/ConstructorHelpers.h"

AH08_MiscGameMode::AH08_MiscGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AH08_MiscPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}