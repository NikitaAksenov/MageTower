// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/MTGameModeBase.h"

#include "Enemy/EnemyTypes.h"

#include "MTBattleGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class MAGETOWER_API AMTBattleGameModeBase : public AMTGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "GameMode")
	FEnemySpawnSettings DefaultSpawnSettings;

public:
	UFUNCTION(BlueprintCallable, Category = "GameMode")
	FEnemySpawnSettings GetDefaultSpawnSettings() const { return DefaultSpawnSettings; }
};
