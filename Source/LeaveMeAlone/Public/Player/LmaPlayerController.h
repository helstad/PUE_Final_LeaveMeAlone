// LeaveMeAlone Game by Ivan Safronov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LmaPlayerController.generated.h"

UCLASS()
class LEAVEMEALONE_API ALmaPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginSpectatingState() override;
	virtual void BeginPlay() override;
};
