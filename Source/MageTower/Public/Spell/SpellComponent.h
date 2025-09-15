// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Core/MTGameStateBase.h"
#include "GameplayTagContainer.h"

#include "SpellComponent.generated.h"


class USpell;


USTRUCT(BlueprintType)
struct FAddSpellInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USpell> SpellClass;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGETOWER_API USpellComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USpellComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Spell")
	TMap<FGameplayTag, USpell*> Spells;

protected:
	UFUNCTION(BlueprintCallable, Category = "Spell")
	void AddSpell(const FAddSpellInfo& InInfo);

	void ClearSpells();

protected:
	UFUNCTION()
	void OnGameFinished(EGameFinishedReason InReason);
};
