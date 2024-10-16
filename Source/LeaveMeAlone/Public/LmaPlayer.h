// LeaveMeAlone Game by Ivan Safronov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Player/LmaDefaultCharacter.h"
#include "LmaPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;

UCLASS()
class LEAVEMEALONE_API ALmaPlayer : public ALmaDefaultCharacter
{
	GENERATED_BODY()

public:
	ALmaPlayer();

protected:
	/** Properties */
	UPROPERTY()
	APlayerController* PlayerController = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Character|Components|Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Character|Components|Camera")
	UCameraComponent* CameraComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* MappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Actions")
	UInputAction* IA_Move;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Actions")
	UInputAction* IA_Look;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Actions")
	UInputAction* IA_Zoom;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser")
	UNiagaraComponent* NiagaraComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Laser")
	UNiagaraSystem* NiagaraSystem = nullptr;
	
	/** Methods */
	
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);
	
	UFUNCTION()
	void Zoom(const FInputActionValue& Value);
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	/** Properties */
	float YRotation = -75.0f;
	float ArmLength = 900.0f;
	float FOV = 55.0f;
	float MinZoom = 400.0f;
	float MaxZoom = 1400.0f;
	float ZoomSpeed = 20.0f;

	FHitResult ResultHit;
	
	void UpdateCursorPosition();
};
