// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"
#include "TGCharacterBase.generated.h"

// The base Character class for the game. Everything with an AbilitySystemComponent in this game will inherit from this class.
// This class should not be instantiated and instead subclassed.
UCLASS()
class TESTGAS_API ATGCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATGCharacterBase(const class FObjectInitializer& ObjectInitializer);

	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Getters for attributes in TGAttributeSet

	// Get MoveSpeed CurrentValue
	UFUNCTION(BlueprintCallable, Category = "CharacterBase|Attributes")
	float GetMoveSpeed() const;

	// Get MoveSpeed BaseValue
	UFUNCTION(BlueprintCallable, Category = "CharacterBase|Attributes")
	float GetMoveSpeedBaseValue() const;

	UFUNCTION(BlueprintCallable, Category = "CharacterBase|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "CharacterBase|Attributes")
	float GetMaxHealth() const;

protected:

	// Instead of TWeakObjectPtrs, you could just have UPROPERTY() hard references or no references at all and just call
	// GetAbilitySystem() and make a GetAttributeSetBase() that can read from the PlayerState or from child classes.
	// Just make sure you test if the pointer is valid before using.
	// I opted for TWeakObjectPtrs because I didn't want a shared hard reference here and I didn't want an extra function call of getting
	// the ASC/AttributeSet from the PlayerState or child classes every time I referenced them in this base class.
	TWeakObjectPtr<class UTGAbilitySystemComponent> AbilitySystemComp;
	TWeakObjectPtr<class UTGAttributeSet> CharAttributeSet;

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterBase|Attributes")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	// Initialize the Character's attributes. Must run on Server but we run it on Client too
	// so that we don't have to wait. The Server's replication to the Client won't matter since
	// the values should be the same.
	virtual void InitializeAttributes();
};