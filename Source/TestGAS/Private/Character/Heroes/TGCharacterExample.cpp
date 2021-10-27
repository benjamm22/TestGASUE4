// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Heroes/TGCharacterExample.h"
#include "Character/TGCharacterBase.h"
#include "Components/TGAbilitySystemComponent.h"
#include "Components/TGCharacterMovementComponent.h"
#include "Attributes/TGAttributeSet.h"
#include "Player/TGPlayerState.h"
#include "Player/TGPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/KismetSystemLibrary.h"


// Constructor
ATGCharacterExample::ATGCharacterExample(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Spring Arm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;

	// Camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>(FName("CameraComp"));
	CameraComp->SetupAttachment(CameraBoom);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Default Values for created variables
	MinSpringArmLength = 50.0f;
	MaxSpringArmLength = 1000.0f;
	ZoomAmount = 20.0f;
	ZoomSensitivity = 2.0f;

	bLeftClickPressed = false;
	bRightClickPressed = false;
}

// Server only
void ATGCharacterExample::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ATGPlayerState* PS = GetPlayerState<ATGPlayerState>();
	if (PS)
	{
		// Set the ASC on the server. Clients do this in OnRep_PlayerState()
		AbilitySystemComp = Cast<UTGAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		// AI won't have PlayerControllers so we can init again here just to be sure.
		// No harm in initing twice for heroes that have PlayerControllers
		// InitAbilityActorInfo(OwnerActor, AvatarActor)
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

		CharAttributeSet = PS->GetTGAttributeSet();

		// Initialize our attributes -- function in TGCharacterBase
		InitializeAttributes();
	}
}

// Client only
// If you get the error message LogAbilitySystem: Warning: Can't activate LocalOnly or LocalPredicted ability %s when not local!
// then you did not initialize your ASC on the client.
void ATGCharacterExample::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	ATGPlayerState* PS = GetPlayerState<ATGPlayerState>();
	if (PS)
	{
		// Set ASC on the client(s). Server does this in PossessedBy()
		AbilitySystemComp = Cast<UTGAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		// Init ASC Actor Info for clients. Server will init its ASC when it possesses a new actor.
		AbilitySystemComp->InitAbilityActorInfo(PS, this);

		CharAttributeSet = PS->GetTGAttributeSet();

		// Initialize our attributes -- function in TGCharacterBase
		InitializeAttributes();
	}
}

// Move forward/back with keyboard -- camera follows if no mouse pressed
void ATGCharacterExample::MoveForward(float Value)
{
	if (Value && bLeftClickPressed)
	{
		AddMovementInput(GetActorForwardVector() * Value);
	}
	else if (Value && bRightClickPressed)
	{
		AddMovementInput(GetActorForwardVector() * Value);
	}
	else if (Value)
	{
		RotateCameraToCharacter();
		AddMovementInput(GetActorForwardVector() * Value);
	}
}

// Movement with the mouse, turns character in direction of controller (camera)
void ATGCharacterExample::MouseForward(float Value)
{
	if (Value && bLeftClickPressed)
	{
		const FRotator Rotation = CameraBoom->GetRelativeRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		GetController()->SetControlRotation(YawRotation);
		AddMovementInput(Direction, Value);
	}
}

// Move (strafe) right/left -- only rotate the camera to the character if no mouse press
void ATGCharacterExample::MoveRight(float Value)
{
	if (Value && bLeftClickPressed)
	{
		AddMovementInput(GetActorRightVector() * Value);
	}
	else if (Value && bRightClickPressed)
	{
		AddMovementInput(GetActorRightVector() * Value);
	}
	else if (Value)
	{
		RotateCameraToCharacter();
		AddMovementInput(GetActorRightVector() * Value);
	}
}

// If the camera is locked, just rotate. If it isn't make camera match/follow our rotation
void ATGCharacterExample::Rotate(float Value)
{
	if (Value && bLeftClickPressed)
	{
		AddControllerYawInput(Value);
	}
	else if (Value && bRightClickPressed)
	{
		AddControllerYawInput(Value);
	}
	else if (Value)
	{
		RotateCameraToCharacter();
		AddControllerYawInput(Value);
	}
}

// Look left to right
void ATGCharacterExample::Turn(float Value)
{
	if (Value)
	{
		CameraBoom->AddRelativeRotation(FRotator(0, Value * 2, 0));
	}
}

// Look up and down
void ATGCharacterExample::LookUp(float Value)
{
	if (Value)
	{
		CameraBoom->AddRelativeRotation(FRotator(Value * 2, 0, 0));
	}
}

// Zoom camera out based on CameraBoom
void ATGCharacterExample::MouseScrollDown()
{
	float Value = CameraBoom->TargetArmLength + (ZoomAmount * ZoomSensitivity);
	CameraBoom->TargetArmLength = FMath::Clamp(Value, MinSpringArmLength, MaxSpringArmLength);
}

// Zoom camera in based on CameraBoom
void ATGCharacterExample::MouseScrollUp()
{
	float Value = CameraBoom->TargetArmLength - (ZoomAmount * ZoomSensitivity);
	CameraBoom->TargetArmLength = FMath::Clamp(Value, MinSpringArmLength, MaxSpringArmLength);
}

// Used to unlock camera
void ATGCharacterExample::LeftClickPressed()
{
	bLeftClickPressed = true;
}

// Used to relock camera
void ATGCharacterExample::LeftClickReleased()
{
	bLeftClickPressed = false;
}

// Unlock the camera when RightClick is pressed
void ATGCharacterExample::RightClickPressed()
{
	bRightClickPressed = true;
}

// Relock camera when RightClick released
void ATGCharacterExample::RightClickReleased()
{
	bRightClickPressed = false;
}

void ATGCharacterExample::MiddleMousePressed()
{
}

void ATGCharacterExample::MiddleMouseReleased()
{
}

// Resets the camera by interpolating the camera rotation to character rotation
void ATGCharacterExample::RotateCameraToCharacter()
{
	FRotator CamRot = CameraBoom->GetRelativeRotation();
	FRotator CharRot = GetActorRotation();

	CameraBoom->SetRelativeRotation(FMath::RInterpConstantTo(CamRot, FRotator(CamRot.Pitch, CharRot.Yaw, CamRot.Roll),
		GetWorld()->DeltaTimeSeconds, 360.0f));
}

// Player Movement
void ATGCharacterExample::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Move
	PlayerInputComponent->BindAxis("MoveForward", this, &ATGCharacterExample::MoveForward);
	PlayerInputComponent->BindAxis("MouseForward", this, &ATGCharacterExample::MouseForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATGCharacterExample::MoveRight);

	// Rotate
	PlayerInputComponent->BindAxis("Rotate", this, &ATGCharacterExample::Rotate);

	// Jump -- ue4 helps with this
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATGCharacterExample::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ATGCharacterExample::StopJumping);

	// Camera Movement
	PlayerInputComponent->BindAxis("Turn", this, &ATGCharacterExample::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ATGCharacterExample::LookUp);

	// Camera Zoom
	PlayerInputComponent->BindAction("MouseScrollDown", IE_Pressed, this, &ATGCharacterExample::MouseScrollDown);
	PlayerInputComponent->BindAction("MouseScrollUp", IE_Released, this, &ATGCharacterExample::MouseScrollUp);

	// Left Click
	PlayerInputComponent->BindAction("LeftClick", IE_Pressed, this, &ATGCharacterExample::LeftClickPressed);
	PlayerInputComponent->BindAction("LeftClick", IE_Released, this, &ATGCharacterExample::LeftClickReleased);

	// Right Click
	PlayerInputComponent->BindAction("RightClick", IE_Pressed, this, &ATGCharacterExample::RightClickPressed);
	PlayerInputComponent->BindAction("RightClick", IE_Released, this, &ATGCharacterExample::RightClickReleased);

	// Middle Mouse
	PlayerInputComponent->BindAction("MiddleMouse", IE_Pressed, this, &ATGCharacterExample::MiddleMousePressed);
	PlayerInputComponent->BindAction("MiddleMouse", IE_Released, this, &ATGCharacterExample::MiddleMouseReleased);
}

