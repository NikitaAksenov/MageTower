// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Enemy/EnemyTypes.h"

#include "MTGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class MAGETOWER_API AMTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "GameMode")
	FEnemySpawnSettings DefaultSpawnSettings;

public:
	UFUNCTION(BlueprintCallable, Category = "GameMode")
	FEnemySpawnSettings GetDefaultSpawnSettings() const { return DefaultSpawnSettings; }
};
