// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

#include "Core/MTGameStateBase.h"
#include "Enemy.h"
#include "EnemyTypes.h"

#include "EnemySpawnSubsystem.generated.h"


class AEnemy;


DECLARE_LOG_CATEGORY_EXTERN(LogEnemySpawnSubsystem, Log, All);


/**
 * 
 */
UCLASS()
class MAGETOWER_API UEnemySpawnSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UEnemySpawnSubsystem, STATGROUP_Tickables); }


public:
	UFUNCTION(BlueprintCallable, Category = "EnemySpawnSubsystem")
	void StartSpawning(const FEnemySpawnSettings& InSpawnSettings);

	UFUNCTION(BlueprintCallable, Category = "EnemySpawnSubsystem")
	void StopSpawning();

	// Bindings
protected:
	UFUNCTION()
	void OnGameStarted();

	UFUNCTION()
	void OnGameFinished(EGameFinishedReason InReason);

protected:
	void ProcessSpawning(float DeltaTime);

	AEnemy* SpawnEnemy(const TSubclassOf<AEnemy>& InEnemyClass, const FVector& InLocation) const;

	FVector FindSpawnLocation() const;

protected:
	bool bSpawning = false;

	TSharedPtr<FEnemySpawnRuntimeData> SpawnRuntimeData = nullptr;
};
