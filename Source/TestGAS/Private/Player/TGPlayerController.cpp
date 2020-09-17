// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TGPlayerController.h"
#include "Player/TGPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Character/Heroes/TGCharacterExample.h"

void ATGPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ATGPlayerState* PS = GetPlayerState<ATGPlayerState>();
	if (PS)
	{
		// Init ASC with PS (owner) and new Pawn (avatar actor)
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
}

void ATGPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}
