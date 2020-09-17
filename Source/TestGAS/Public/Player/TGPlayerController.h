// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TGPlayerController.generated.h"

// In multiplayer games the PlayerController only exists on the owning client and the server. 
// This means in a game of 4 players, the server has 4 player controllers, and each client only has 1. 
// This is very important in understanding where to put certain variables as when all players require a player’s variable 
// to be replicated it should never exist in the PlayerController but in the Pawn or even PlayerState instead.

// I would keep movement on the pawn. It's cleaner keeping functions you only do on a character on the character. 
// Controller is better for anything you can do while unpossessed or while possessing an actor like menus, maps, score screens. 
// I can't fire when I'm not possessing an actor so why would I need firing script on my controller.

UCLASS()
class TESTGAS_API ATGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

protected:

	// Server
	virtual void OnPossess(APawn* InPawn) override;
	
	// Client
	virtual void OnRep_PlayerState() override;
	
};
