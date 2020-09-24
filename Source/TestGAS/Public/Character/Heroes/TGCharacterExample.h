// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TGCharacterBase.h"
#include "TGCharacterExample.generated.h"

// For player controlled characters where the ASC lives on the PlayerState,
// I typically initialize the server in the Pawn's PossessedBy() function and 
// initialize on the client in the Pawn's OnRep_PlayerState() function. This ensures that the PlayerState exists on the client.
UCLASS()
class TESTGAS_API ATGCharacterExample : public ATGCharacterBase
{
	GENERATED_BODY()

public:

	ATGCharacterExample(const class FObjectInitializer& ObjectInitializer);

	// Only called on the server -- calls before Server's AcknowledgePossession()
	virtual void PossessedBy(AController* NewController) override;

	// Input Component
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:

	// Client only
	virtual void OnRep_PlayerState() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* CameraBoom;

	UFUNCTION()
	void MoveForward(float Value);
	
	UFUNCTION()
	void MouseForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void Rotate(float Value);

	UFUNCTION()
	void Turn(float Value);

	UFUNCTION()
	void LookUp(float Value);

	UFUNCTION()
	void MouseScrollDown();

	UFUNCTION()
	void MouseScrollUp();

	UFUNCTION()
	void LeftClickPressed();

	UFUNCTION()
	void LeftClickReleased();

	UFUNCTION()
	void RightClickPressed();

	UFUNCTION()
	void RightClickReleased();

	UFUNCTION()
	void MiddleMousePressed();

	UFUNCTION()
	void MiddleMouseReleased();

	UFUNCTION()
	void RotateCameraToCharacter();

	UPROPERTY(EditDefaultsOnly, Category = "CharacterExample|CameraControls")
	float ZoomAmount;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterExample|CameraControls")
	float ZoomSensitivity;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterExample|CameraControls")
	float MinSpringArmLength;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterExample|CameraControls")
	float MaxSpringArmLength;

	UPROPERTY()
	bool bLeftClickPressed;

	UPROPERTY()
	bool bRightClickPressed;
};
