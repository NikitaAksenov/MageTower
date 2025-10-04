// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/SavesSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Save/MTSaveGame.h"
#include "Save/SaveableInterface.h"


DEFINE_LOG_CATEGORY(LogSavesSubsystem);


void USavesSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0)) 
	{
		UE_LOG(LogSavesSubsystem, Log, TEXT("Save game [%s] exists, getting it from slot"), *SaveSlotName);
		
		CurrentSaveGame = Cast<UMTSaveGame>(
			UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	}
	else
	{
		UE_LOG(LogSavesSubsystem, Log, TEXT("Save game [%s] does not exist, creating"), *SaveSlotName);

		CurrentSaveGame = Cast<UMTSaveGame>(
			UGameplayStatics::CreateSaveGameObject(UMTSaveGame::StaticClass()));
	}
}

void USavesSubsystem::RegisterSaveableObject(ISaveableInterface* InSaveableObject)
{
	if (!InSaveableObject) return;

	if (SaveableObjects.Contains(InSaveableObject))
	{
		UE_LOG(LogSavesSubsystem, Warning, TEXT("Saveable object %s is already registered"), *GetNameSafe(Cast<UObject>(InSaveableObject)));
		return;
	}
	
	SaveableObjects.Add(InSaveableObject);

	UE_LOG(LogSavesSubsystem, Log, TEXT("Saveable object %s registered"), *GetNameSafe(Cast<UObject>(InSaveableObject)));
}

void USavesSubsystem::UnRegisterSaveableObject(ISaveableInterface* InSaveableObject)
{
	if (!InSaveableObject) return;

	if (!SaveableObjects.Contains(InSaveableObject))
	{
		UE_LOG(LogSavesSubsystem, Warning, TEXT("Saveable object %s is not registered"), *GetNameSafe(Cast<UObject>(InSaveableObject)));
		return;
	}

	SaveableObjects.Remove(InSaveableObject);

	UE_LOG(LogSavesSubsystem, Log, TEXT("Saveable object %s unregistered"), *GetNameSafe(Cast<UObject>(InSaveableObject)));

}

void USavesSubsystem::SaveGame()
{
	check(CurrentSaveGame);
	
	UE_LOG(LogSavesSubsystem, Log, TEXT("Save game"));

	for (ISaveableInterface* SaveableObject : SaveableObjects)
	{
		SaveableObject->HandleSave(CurrentSaveGame);
	}

	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SaveSlotName, 0);
}

void USavesSubsystem::LoadGame()
{
	check(CurrentSaveGame);

	UE_LOG(LogSavesSubsystem, Log, TEXT("Load game"));

	for (ISaveableInterface* SaveableObject : SaveableObjects)
	{
		SaveableObject->HandleLoad(CurrentSaveGame);
	}
}
