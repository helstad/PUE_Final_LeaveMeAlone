// LeaveMeAlone Game by Ivan Safronov. All Rights Reserved.


#include "Player/LmaPlayerController.h"

void ALmaPlayerController::BeginSpectatingState()
{
	SetControlRotation(FRotator(-75.0f,0.0f,0.0f));
	Super::BeginSpectatingState();
}

void ALmaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}