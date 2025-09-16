// Fill out your copyright notice in the Description page of Project Settings.


#include "Statics/MageTowerFunctionLibrary.h"

#include "Core/MTGameModeBase.h"
#include "Core/MTGameStateBase.h"


AMTGameStateBase* UMageTowerFunctionLibrary::GetMTGameState(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;

	const UWorld* World = WorldContextObject->GetWorld();
	if (!World) return nullptr;
	
	return Cast<AMTGameStateBase>(World->GetGameState());
}

AMTGameModeBase* UMageTowerFunctionLibrary::GetMTGameMode(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;

	const UWorld* World = WorldContextObject->GetWorld();
	if (!World) return nullptr;

	return Cast<AMTGameModeBase>(World->GetAuthGameMode());
}
