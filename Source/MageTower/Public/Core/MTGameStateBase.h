// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "MTGameStateBase.generated.h"


class ATower;


DECLARE_LOG_CATEGORY_EXTERN(LogEnemy, Log, All);


UENUM()
enum class EGameStage : uint8
{
	None,
	InProgress,
	Finished,
};

UENUM()
enum class EGameFinishedReason : uint8
{
	Exit,
	Win,
	Lose,
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStateEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameFinishedDelegate, EGameFinishedReason, Reason);


/**
 * 
 */
UCLASS()
class MAGETOWER_API AMTGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "GameState")
	EGameStage CurrentGameStage = EGameStage::None;

public:
	UPROPERTY(BlueprintAssignable, Category = "GameState")
	FGameStateEvent OnGameStartedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GameState")
	FOnGameFinishedDelegate OnGameFinishedDelegate;

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
