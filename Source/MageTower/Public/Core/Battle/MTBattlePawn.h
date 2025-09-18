// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/MTPawn.h"

#include "MTBattlePawn.generated.h"


/**
 * 
 */
UCLASS()
class MAGETOWER_API AMTBattlePawn : public AMTPawn
{
	GENERATED_BODY()

public:
	AMTBattlePawn();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpellComponent> SpellComponent;
};
