// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TGCharacterMovementComponent.generated.h"

// Overrides the CharacterMovmentComponent so we can combine with attributes
UCLASS()
class TESTGAS_API UTGCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	UTGCharacterMovementComponent();

	virtual float GetMaxSpeed() const override;
};
