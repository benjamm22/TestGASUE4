// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TGCharacterBase.h"
#include "Attributes/TGAttributeSet.h"
#include "Components/TGAbilitySystemComponent.h"
#include "Components/TGCharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values and set the default CharacterMovementComponent to TGCharacterMovementComponent
ATGCharacterBase::ATGCharacterBase(const class FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UTGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Don't call Tick() every frame.
	PrimaryActorTick.bCanEverTick = false;

	bAlwaysRelevant = true;
}

UAbilitySystemComponent* ATGCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp.Get();
}

// Getters for attributes from TGAttributeSet

float ATGCharacterBase::GetMoveSpeed() const
{
	if (CharAttributeSet.IsValid())
	{
		return CharAttributeSet->GetMoveSpeed();
	}

	return 0.0f;
}

float ATGCharacterBase::GetMoveSpeedBaseValue() const
{
	if (CharAttributeSet.IsValid())
	{
		return CharAttributeSet->GetMoveSpeedAttribute().GetGameplayAttributeData(CharAttributeSet.Get())->GetBaseValue();
	}

	return 0.0f;
}

// Attribute Intialization
void ATGCharacterBase::InitializeAttributes()
{
	if (!AbilitySystemComp.IsValid())
	{
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on server and client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComp->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComp->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle =
			AbilitySystemComp->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComp.Get());
	}
}
