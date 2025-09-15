// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell/SpellComponent.h"

#include "Core/MTGameStateBase.h"
#include "Spell/Spell.h"
#include "Spell/SpellTypes.h"
#include "Statics/MageTowerFunctionLibrary.h"


USpellComponent::USpellComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USpellComponent::BeginPlay()
{
	Super::BeginPlay();

	UMageTowerFunctionLibrary::GetMTGameState(this)->OnGameFinishedDelegate.AddDynamic(this, &ThisClass::OnGameFinished);
}

void USpellComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (const auto& SpellPair : Spells)
	{
		USpell* Spell = SpellPair.Value;
		Spell->Tick(DeltaTime);
	}
}

void USpellComponent::AddSpell(const FAddSpellInfo& InInfo)
{
	USpell* Spell = NewObject<USpell>(this, InInfo.SpellClass);

	UE_LOG(LogSpell, Log, TEXT("Adding spell %s to %s"), *Spell->GetName(), *GetOwner()->GetName());

	const FGameplayTag SpellTag = Spell->GetSpellTag();
	if (Spells.Contains(SpellTag))
	{
		UE_LOG(LogSpell, Warning, TEXT("%s already has spell with tag %s"), *GetOwner()->GetName(), *SpellTag.ToString());

		Spell->MarkAsGarbage();
		return;
	}

	Spells.Add(SpellTag, Spell);

	Spell->RegisterSpell(this);
}

void USpellComponent::ClearSpells()
{
	UE_LOG(LogSpell, Log, TEXT("Clearing spells"));
	
	for (const auto& SpellPair : Spells)
	{
		USpell* Spell = SpellPair.Value;
		Spell->MarkAsGarbage();
	}

	Spells.Empty();
}

void USpellComponent::OnGameFinished(EGameFinishedReason InReason)
{
	ClearSpells();
}
