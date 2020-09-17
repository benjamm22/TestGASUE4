// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "TGPlayerState.generated.h"

// A PlayerState is a container for variables to replicate between client/server for a specific player. 
// For multiplayer games, it’s not supposed to run logic, and is just data container since PlayerController is not available on 
// all clients and Pawn are often destroyed when a player dies so unsuitable for data that needs to be stored even after death.

// Owner Actor holds the ASC - Physical representation of the ASC is the Avatar Actor (these don't have to be the same actor)
// So the ASC is on the PlayerState making it the Owner Actor -- the Avatar Actor will be our Controlled Character

// If your Actor will respawn and need persistence of Attributes or GameplayEffects between spawns (like a hero in a MOBA), 
// then the ideal location for the ASC is on the PlayerState.

// If your ASC is on PlayerState, increase NetUpdateFrequency of the PlayerState (by default it's a low value -- causes lag)

// Both, the OwnerActor and the AvatarActor if different Actors, should implement the IAbilitySystemInterface. 
// This interface has one function that must be overriden, UAbilitySystemComponent* GetAbilitySystemComponent() const, 
// which returns a pointer to its ASC. 
// ASCs interact with each other internally to the system by looking for this interface function.

UCLASS()
class TESTGAS_API ATGPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	ATGPlayerState();

	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	class UTGAttributeSet* GetTGAttributeSet() const;

	// Getters from attributes in TGAttributeSet

	UFUNCTION(BlueprintCallable, Category = "TGPlayerState|Attributes")
	float GetMoveSpeed() const;

protected:

	class UTGAbilitySystemComponent* AbilitySystemComp;

	class UTGAttributeSet* CharAttributeSet;
};
