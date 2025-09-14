// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell/Player/PlayerSpell.h"

#include "Core/MTPawn.h"
#include "Core/MTPlayerController.h"
#include "Spell/SpellComponent.h"


void UPlayerSpell::RegisterSpell(USpellComponent* InSpellComponent)
{
	Super::RegisterSpell(InSpellComponent);

	Pawn = Cast<AMTPawn>(InSpellComponent->GetOwner());
	check(Pawn);

	Controller = Cast<AMTPlayerController>(Pawn->GetController());
	check(Controller);
}
