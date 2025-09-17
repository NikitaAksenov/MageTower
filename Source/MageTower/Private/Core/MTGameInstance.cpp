// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MTGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Save/MTSaveGame.h"


void UMTGameInstance::LoadGame()
{
	if (UGameplayStatics::DoesSaveGameExist(TEXT("MageTowerSlot"), 0))
	{
		CurrentSave = Cast<UMTSaveGame>(
			UGameplayStatics::LoadGameFromSlot(TEXT("MageTowerSlot"), 0));
	}
	else
	{
		CurrentSave = Cast<UMTSaveGame>(
			UGameplayStatics::CreateSaveGameObject(UMTSaveGame::StaticClass()));
	}

	CurrentSave->Load(GetWorld());
}

void UMTGameInstance::SaveGame()
{
	if (CurrentSave)
	{
		CurrentSave->Save(GetWorld());

		UGameplayStatics::SaveGameToSlot(CurrentSave, TEXT("MageTowerSlot"), 0);
	}
}
