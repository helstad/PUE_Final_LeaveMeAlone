// LeaveMeAlone Game by Ivan Safronov. All Rights Reserved.

#include "Player/LmaDefaultCharacter.h"

ALmaDefaultCharacter::ALmaDefaultCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALmaDefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ALmaDefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALmaDefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

