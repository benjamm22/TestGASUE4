// Fill out your copyright notice in the Description page of Project Settings.


#include "TGEngineSubsystem.h"
#include "AbilitySystemGlobals.h"

// Allegedly allows for GAS target data in verions 4.24+
void UTGEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UAbilitySystemGlobals::Get().InitGlobalData();
}