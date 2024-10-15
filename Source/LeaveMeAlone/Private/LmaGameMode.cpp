// LeaveMeAlone Game by Ivan Safronov. All Rights Reserved.

#include "LmaGameMode.h"

#include "Player/LmaDefaultCharacter.h"
#include "Player/LmaPlayerController.h"

ALmaGameMode::ALmaGameMode()
{
	DefaultPawnClass = ALmaDefaultCharacter::StaticClass();
	PlayerControllerClass = ALmaPlayerController::StaticClass();
}