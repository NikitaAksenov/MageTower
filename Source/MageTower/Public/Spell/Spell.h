// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "GameplayTagContainer.h"

#include "Spell.generated.h"


class USpellComponent;


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
	
protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Spell")
	USpellComponent* OwningSpellComponent;

public:
	virtual void RegisterSpell(USpellComponent* InSpellComponent);

	virtual void Tick(float DeltaTime);

public:
	UFUNCTION(BlueprintCallable, Category = "Spell")
	USpellComponent* GetOwningSpellComponent() const { return OwningSpellComponent; }

	UFUNCTION(BlueprintCallable, Category = "Spell")
	FGameplayTag GetSpellTag() const { return SpellTag; }
};
