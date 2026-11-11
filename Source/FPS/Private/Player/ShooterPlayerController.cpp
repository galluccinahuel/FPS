// Copyright Gallucci Nahuel.


#include "Player/ShooterPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

AShooterPlayerController::AShooterPlayerController()
{
	bReplicates = true;
	
}

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if (IsValid(SubSystem))
	{
		SubSystem->AddMappingContext(ShooterIMC, 0);
	}
	
}

void AShooterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* ShooterInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	ShooterInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::Input_Move);
	ShooterInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterPlayerController::Input_Look);
	ShooterInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AShooterPlayerController::Input_Jump);
	ShooterInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AShooterPlayerController::Input_Crouch);
}

void AShooterPlayerController::Input_Crouch()
{
	if (!IsValid(GetCharacter())) return;
	
	if (UCharacterMovementComponent* CMC = GetCharacter()->GetCharacterMovement())
	{
		if (!IsValid(CMC)) return;
		CMC->bWantsToCrouch = !CMC->bWantsToCrouch;
	}
	
}

void AShooterPlayerController::Input_Jump()
{
	if (!IsValid(GetCharacter())) return;
	
	UCharacterMovementComponent* CMC = GetCharacter()->GetCharacterMovement();
	if (!IsValid(CMC)) return;
	
	if (CMC->bWantsToCrouch)
	{
		CMC->bWantsToCrouch = false;
	}
	else
	{
		GetCharacter()->Jump();
	}
	
	
}

void AShooterPlayerController::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	
	const FRotator Rotation = GetControlRotation();
	
	const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);
	
	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	
	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardVector, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightVector, InputAxisVector.X);
	}
	
	
	
}

void AShooterPlayerController::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	
	AddYawInput(InputAxisVector.X);
	AddPitchInput(InputAxisVector.Y);
	
	
	
}
