// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "Resources/ResourceTypes.h"
#include "Save/SaveableInterface.h"

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
class MAGETOWER_API AMTGameStateBase :
	public AGameStateBase,
	public ISaveableInterface
{
	GENERATED_BODY()

public:
	AMTGameStateBase();
	
	//~ Start ISaveableInterface interface
public:
	virtual void HandleSave(UMTSaveGame* InSaveGame) override;
	virtual void HandleLoad(UMTSaveGame* InSaveGame) override;
	//~ End   ISaveableInterface interface


	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


protected:
	UPROPERTY(VisibleInstanceOnly, Category = "GameState")
	FResourceContainer ResourceContainer;

public:
	UPROPERTY(BlueprintAssignable, Category = "GameState")
	FGameStateEvent OnGameStartedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GameState")
	FOnGameFinishedDelegate OnGameFinishedDelegate;

public:
	UFUNCTION(BlueprintCallable, Category = "GameState")
	FResourceContainer GetResourceContainer() const { return ResourceContainer; }

	UFUNCTION(BlueprintCallable, Category = "GameState")
	FResourceContainer& GetResourceContainerRef() { return ResourceContainer; }
};
