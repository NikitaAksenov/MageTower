// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell/Spell.h"

#include "PlayerSpell.generated.h"


class AMTPawn;
class AMTPlayerController;


/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class MAGETOWER_API UPlayerSpell : public USpell
{
	GENERATED_BODY()

	//~ Start USpell Interface
public:
	virtual void RegisterSpell(USpellComponent* InSpellComponent) override;
	//~ End   USpell Interface

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Spell")
	AMTPawn* Pawn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Spell")
	AMTPlayerController* Controller;
};
