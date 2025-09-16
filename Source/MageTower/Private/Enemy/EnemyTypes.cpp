// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyTypes.h"


FEnemySpawnRuntimeData::FEnemySpawnRuntimeData()
{
	SpawnSettings = FEnemySpawnSettings();
}

FEnemySpawnRuntimeData::FEnemySpawnRuntimeData(const FEnemySpawnSettings& InSpawnSettings)
{
	SpawnSettings = InSpawnSettings;
	DurationSinceLastSpawn = SpawnSettings.SpawnRate;
}

TSubclassOf<AEnemy> FEnemySpawnRuntimeData::GetEnemyClass() const
{
	return SpawnSettings.EnemyClass;
}