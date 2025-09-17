// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "Resources/ResourceTypes.h"

#include "MTSaveGame.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogMTSaveGame, Log, All);


/**
 * 
 */
UCLASS()
class MAGETOWER_API UMTSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UMTSaveGame();

public:
	UPROPERTY(VisibleAnywhere)
	FResourceContainer ResourceContainer;

public:
	void Save(const UObject* WorldContextObject);
	void Load(const UObject* WorldContextObject);
};
