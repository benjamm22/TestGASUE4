// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TGCharacterMovementComponent.h"
#include "Character/TGCharacterBase.h"

// Constructor
UTGCharacterMovementComponent::UTGCharacterMovementComponent()
{
	bUseControllerDesiredRotation = true;
	bOrientRotationToMovement = false;

	JumpZVelocity = 475.0f;
	AirControl = 0.0f;
	AirControlBoostMultiplier = 0.0f;
	AirControlBoostVelocityThreshold = 0.0f;

	GroundFriction = 15.0f;
	MaxAcceleration = 15000.0f;

	// Values such as a sprint modifier go here
}

float UTGCharacterMovementComponent::GetMaxSpeed() const
{
	ATGCharacterBase* Owner = Cast<ATGCharacterBase>(GetOwner());
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() No Owner"), *FString(__FUNCTION__));
		return Super::GetMaxSpeed();
	}

	return Owner->GetMoveSpeed();
}