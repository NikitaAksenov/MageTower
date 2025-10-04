// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "SavesSubsystem.generated.h"


class ISaveableInterface;
class UMTSaveGame;


DECLARE_LOG_CATEGORY_EXTERN(LogSavesSubsystem, Log, All);


/**
 * 
 */
UCLASS()
class MAGETOWER_API USavesSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	void RegisterSaveableObject(ISaveableInterface* InSaveableObject);
	void UnRegisterSaveableObject(ISaveableInterface* InSaveableObject);

	void SaveGame();
	void LoadGame();

protected:
	UPROPERTY()
	UMTSaveGame* CurrentSaveGame;

	UPROPERTY()
	TArray<ISaveableInterface*> SaveableObjects;

protected:
	FString SaveSlotName = "DefaultSave";
};
