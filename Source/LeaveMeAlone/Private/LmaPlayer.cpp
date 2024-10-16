// LeaveMeAlone Game by Ivan Safronov. All Rights Reserved.


#include "LmaPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ALmaPlayer::ALmaPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = ArmLength;
	SpringArmComponent->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bEnableCameraLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetFieldOfView(FOV);
	CameraComponent->bUsePawnControlRotation = false;

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	NiagaraComponent->SetupAttachment(GetRootComponent());
	NiagaraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void ALmaPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ALmaPlayer::Move);
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ALmaPlayer::Look);
		EnhancedInputComponent->BindAction(IA_Zoom, ETriggerEvent::Triggered, this, &ALmaPlayer::Zoom);
	}
}

void ALmaPlayer::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}

	if (NiagaraSystem)
	{
		NiagaraComponent->SetAsset(NiagaraSystem);
		NiagaraComponent->Activate(true);
	}
}

void ALmaPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCursorPosition();
}

void ALmaPlayer::UpdateCursorPosition()
{
	if (PlayerController)
	{
		PlayerController->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);

		if (ResultHit.IsValidBlockingHit())
		{
			float FindRotatorResultYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ResultHit.Location).Yaw;
			SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResultYaw, 0.0f)));
			const FVector CursorLocation = ResultHit.Location;
		}
	}
}

void ALmaPlayer::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator YawRotation = SpringArmComponent->GetComponentRotation();
		const FVector  ForwardDirection = FVector::VectorPlaneProject(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), FVector::UpVector).GetSafeNormal();
		const FVector  RightDirection = FVector::VectorPlaneProject(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), FVector::UpVector).GetSafeNormal();

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ALmaPlayer::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);

		UpdateCursorPosition();
	}
}

void ALmaPlayer::Zoom(const FInputActionValue& Value)
{
	const float ZoomAxis = Value.Get<float>();
	SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength - ZoomAxis * ZoomSpeed, MinZoom, MaxZoom);
}