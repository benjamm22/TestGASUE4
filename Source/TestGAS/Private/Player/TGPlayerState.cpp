// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TGPlayerState.h"
#include "Player/TGPlayerController.h"
#include "Components/TGAbilitySystemComponent.h"
#include "Character/Heroes/TGCharacterExample.h"
#include "Attributes/TGAttributeSet.h"

ATGPlayerState::ATGPlayerState()
{
	// Create ability system component and force replication
	// ASCs are typically constructed in the OwnerActor's constructor and explicitly marked replicated. (must be c++)
	// Mixed mode means we only are replicated the GEs to ourself, not the GEs to simulated proxies. 
	// If another GDPlayerState (Hero) receives a GE, we won't be told about it by the Server.
	// Attributes, GameplayTags, and GameplayCues will still replicate to us.
	// Full is for single player
	// Mixed is for multiplayer with player controlled actors
	// Minimal is for multiplayer with AI controlled actors
	AbilitySystemComp = CreateDefaultSubobject<UTGAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AbilitySystemComp->SetIsReplicated(true);
	AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	// Create the attribute set, this replicates by default
	// Adding it as a subobject of the owning actor of an AbilitySystemComponent
	// automatically registers the AttributeSet with the AbilitySystemComponent
	CharAttributeSet = CreateDefaultSubobject<UTGAttributeSet>(TEXT("CharAttributeSet"));

	// Set PlayerState's NetUpdateFrequency to the same as the Character.
	// Default is very low for PlayerStates and introduces perceived lag in the ability system.
	// 100 is probably way too high for a shipping game, you can adjust to fit your needs.
	NetUpdateFrequency = 100.0f;
}

UAbilitySystemComponent* ATGPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

UTGAttributeSet* ATGPlayerState::GetTGAttributeSet() const
{
	return CharAttributeSet;
}

// Getters from attributes in TGAttributeSet

float ATGPlayerState::GetMoveSpeed() const
{
	return CharAttributeSet->GetMoveSpeed();
}
