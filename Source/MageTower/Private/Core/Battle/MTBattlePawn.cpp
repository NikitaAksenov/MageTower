// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Battle/MTBattlePawn.h"

#include "Spell/SpellComponent.h"


AMTBattlePawn::AMTBattlePawn()
{
	SpellComponent = CreateDefaultSubobject<USpellComponent>(TEXT("SpellComponent"));
}
