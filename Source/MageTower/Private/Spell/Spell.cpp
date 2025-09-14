// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell/Spell.h"

#include "Spell/SpellComponent.h"


UWorld* USpell::GetWorld() const
{
	return OwningSpellComponent ? OwningSpellComponent->GetWorld() : nullptr;
}

void USpell::Tick(float DeltaTime)
{
	
}

void USpell::RegisterSpell(USpellComponent* InSpellComponent)
{
	if (!InSpellComponent) return;

	if (OwningSpellComponent) return;

	OwningSpellComponent = InSpellComponent;
}
