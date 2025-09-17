// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/MTSaveGame.h"

#include "Core/MTGameStateBase.h"
#include "Statics/MageTowerFunctionLibrary.h"


DEFINE_LOG_CATEGORY(LogMTSaveGame);


UMTSaveGame::UMTSaveGame()
{
}

void UMTSaveGame::Save(const UObject* WorldContextObject)
{
	FResourceContainer SavingContainer = UMageTowerFunctionLibrary::GetMTGameState(WorldContextObject)->GetResourceContainer();
	ResourceContainer = SavingContainer;
}

void UMTSaveGame::Load(const UObject* WorldContextObject)
{		
	UMageTowerFunctionLibrary::GetMTGameState(WorldContextObject)->GetResourceContainerRef().Add(ResourceContainer);
}
