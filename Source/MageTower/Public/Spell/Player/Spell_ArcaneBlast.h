// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell/Player/PlayerSpell.h"

#include "Spell_ArcaneBlast.generated.h"


/**
 * 
 */
UCLASS()
class MAGETOWER_API USpell_ArcaneBlast : public UPlayerSpell
{
	GENERATED_BODY()

public:
	USpell_ArcaneBlast();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnSpellActivated() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spell|Settings")
	float Radius = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spell|Settings")
	float Damage = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spell|Settings")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	
	UPROPERTY(EditDefaultsOnly, Category = "Spell|Settings")
	TEnumAsByte<ECollisionChannel> DamageCollisionChannel = ECollisionChannel::ECC_Pawn;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Spell|Runtime")
	float CooldownDuration = 0.f;
	
	UPROPERTY(VisibleInstanceOnly, Category = "Spell|Runtime")
	FVector LocationUnderCursor;
};
