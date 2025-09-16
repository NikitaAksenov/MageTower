// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Enemy.h"

#include "EnemyTypes.generated.h"


USTRUCT(BlueprintType)
struct FEnemySpawnSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEnemy> EnemyClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRate;
};

USTRUCT()
struct FEnemySpawnRuntimeData
{
	GENERATED_BODY()

public:
	FEnemySpawnRuntimeData();
	explicit FEnemySpawnRuntimeData(const FEnemySpawnSettings& InSpawnSettings);

public:
	FEnemySpawnSettings SpawnSettings;

	float DurationSinceLastSpawn = 0.f;

public:
	TSubclassOf<AEnemy> GetEnemyClass() const;
};