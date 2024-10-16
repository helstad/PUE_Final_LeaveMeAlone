// LeaveMeAlone Game by Ivan Safronov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LmaDefaultCharacter.generated.h"

UCLASS()
class LEAVEMEALONE_API ALmaDefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALmaDefaultCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	virtual void BeginPlay() override;
};
