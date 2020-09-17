// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "TGEngineSubsystem.generated.h"

// Currently needed for target data in GAS in versions 4.24+
UCLASS()
class TESTGAS_API UTGEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
	
public:

	// Allegedly must be called for target data in versions 4.24+
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
