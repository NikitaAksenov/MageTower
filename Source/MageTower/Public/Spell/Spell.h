// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "GameplayTagContainer.h"

#include "Spell.generated.h"


class USpellComponent;


UENUM()
enum class ESpellState : uint8
{
	Ready,
	Active,
	Cooldown,
};

UENUM()
enum class ESpellFinishReason : uint8
{
	Finished,
	Cancelled,
};


/**
 * 
 */
UCLASS(Abstract)
class MAGETOWER_API USpell : public UObject
{
	GENERATED_BODY()

	//~ Start UObject interface
public:
	virtual UWorld* GetWorld() const override;
	//~ End   UObject interface

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell", meta = (Categories = "Spell.ID"))
	FGameplayTag SpellTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell", meta = (UIMin = 0.f, ClampMin = 0.f, ForceUnits = "seconds"))
	float Cooldown = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell")
	bool bActivateOnReady = false;
	
protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Spell")
	USpellComponent* OwningSpellComponent;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Spell")
	ESpellState State = ESpellState::Ready;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Spell")
	float CurrentCooldown = 0.f;

public:
	virtual void RegisterSpell(USpellComponent* InSpellComponent);

	virtual void Tick(float DeltaTime);

private:
	void ReadySpell();
	void ActivateSpell();
	void CooldownSpell();

protected:
	void FinishSpell(ESpellFinishReason InReason);

	virtual void OnSpellReady();
	virtual void OnSpellActivated();
	virtual void OnSpellCooldown();
	virtual void OnSpellFinished(ESpellFinishReason InReason);

public:
	UFUNCTION(BlueprintCallable, Category = "Spell")
	USpellComponent* GetOwningSpellComponent() const { return OwningSpellComponent; }

	UFUNCTION(BlueprintCallable, Category = "Spell")
	FGameplayTag GetSpellTag() const { return SpellTag; }

	UFUNCTION(BlueprintCallable, Category = "Spell")
	float GetCooldownPercentage() const { return Cooldown == 0.f ? 0.f : CurrentCooldown / Cooldown; }
};
