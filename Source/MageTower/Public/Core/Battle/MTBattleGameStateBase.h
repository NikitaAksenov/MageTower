// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/MTGameStateBase.h"

#include "MTBattleGameStateBase.generated.h"


/**
 * 
 */
UCLASS()
class MAGETOWER_API AMTBattleGameStateBase : public AMTGameStateBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "GameState")
	EGameStage CurrentGameStage = EGameStage::None;

public:
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void StartGame();
	
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void FinishGame(EGameFinishedReason InReason);

	UFUNCTION(BlueprintCallable, Category = "GameState")
	FORCEINLINE bool IsGameInProgress() const { return CurrentGameStage == EGameStage::InProgress; }

protected:
	UFUNCTION()
	void OnTowerDestroyed(ATower* InTower);

protected:
	ATower* Tower;
};
