// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TGAttributeSet.generated.h"

// Attributes are float values defined by the struct FGameplayAttributeData.
// These can represent anything from the amount of health a character has to the character's 
// level to the number of charges that a potion has. 
// If it is a gameplay-related numerical value belonging to an Actor, you should consider using an Attribute for it. 
// Attributes should generally only be modified by GameplayEffects so that the ASC can predict the changes.

// Attributes live in an AttributeSet which is responsible for replicating attributes marked for replication
// Attributes have BaseValue and CurrentValue -- Base is permanent value -- Current is the currently modified BaseValue
// For example if you have move speed attribute value of 500 -- a move speed debuff could change current to be 450 until expires
// Once expired, CurrentValue would revert back to 500 (same as BaseValue)

// Some Attributes are treated as placeholders for temporary values that are intended to interact with Attributes. 
// These are called Meta Attributes. For example, we commonly define damage as a Meta Attribute. 
// Instead of a GameplayEffect directly changing our health Attribute, we use a Meta Attribute called damage as a placeholder.
// The damage Meta Attribute has no persistence between GameplayEffects and is overriden by every one. 
// Meta Attributes are not typically replicated.

// Creating an AttributeSet in an OwnerActor's constructor automatically registers it with its ASC. This must be done in C++.
// An ASC can have many AttributeSets -- these have very low memory overhead so if you wanna make a ton... make a ton

// A good example of using multiple would be having 2 attribute sets... one has health and mana -- the other health and rage
// You would then give the set with mana to a wizard and the one with rage to a berzerker


// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class TESTGAS_API UTGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UTGAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// MoveSpeed attribute -- for how fast characters can move
	UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed", ReplicatedUsing = OnRep_MoveSpeed)
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UTGAttributeSet, MoveSpeed)

	// Current Health, when 0 we expect owner to die unless prevented by an ability. Capped by MaxHealth.
	// Positive changes can directly use this.
	// Negative changes to Health should go through Damage meta attribute.
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UTGAttributeSet, Health)

	// MaxHealth is its own attribute since GameplayEffects may modify it
	UPROPERTY(BlueprintReadOnly, Category = "MaxHealth", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UTGAttributeSet, MaxHealth)

protected:

	// Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes.
	// (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before)
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute,
		float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	// These OnRep functions exist to make sure that the ability system internal representations
	// are synchronized properly during replication

	UFUNCTION()
	virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed);

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

};