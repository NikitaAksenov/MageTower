// Fill out your copyright notice in the Description page of Project Settings.


#include "Statics/MageTowerFunctionLibrary.h"

#include "Core/Battle/MTBattleGameModeBase.h"
#include "Core/Battle/MTBattleGameStateBase.h"
#include "Core/MTGameInstance.h"
#include "Core/MTGameModeBase.h"
#include "Core/MTGameStateBase.h"
#include "Core/Upgrade/MTUpgradeGameModeBase.h"
#include "Core/Upgrade/MTUpgradeGameStateBase.h"
#include "Save/SavesSubsystem.h"


AMTGameStateBase* UMageTowerFunctionLibrary::GetMTGameState(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;

	const UWorld* World = WorldContextObject->GetWorld();
	if (!World) return nullptr;
	
	return Cast<AMTGameStateBase>(World->GetGameState());
}

AMTBattleGameStateBase* UMageTowerFunctionLibrary::GetMTBattleGameState(const UObject* WorldContextObject)
{
	return Cast<AMTBattleGameStateBase>(GetMTGameState(WorldContextObject));
}

AMTUpgradeGameStateBase* UMageTowerFunctionLibrary::GetMTUpgradeGameState(const UObject* WorldContextObject)
{
	return Cast<AMTUpgradeGameStateBase>(GetMTGameState(WorldContextObject));
}

AMTGameModeBase* UMageTowerFunctionLibrary::GetMTGameMode(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;

	const UWorld* World = WorldContextObject->GetWorld();
	if (!World) return nullptr;

	return Cast<AMTGameModeBase>(World->GetAuthGameMode());
}

AMTBattleGameModeBase* UMageTowerFunctionLibrary::GetMTBattleGameMode(const UObject* WorldContextObject)
{
	AMTGameModeBase* GameMode = GetMTGameMode(WorldContextObject);
	return Cast<AMTBattleGameModeBase>(GameMode);
}

AMTUpgradeGameModeBase* UMageTowerFunctionLibrary::GetMTUpgradeGameMode(const UObject* WorldContextObject)
{
	return Cast<AMTUpgradeGameModeBase>(GetMTGameMode(WorldContextObject));
}

UMTGameInstance* UMageTowerFunctionLibrary::GetMTGameInstance(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;

	const UWorld* World = WorldContextObject->GetWorld();
	if (!World) return nullptr;

	return Cast<UMTGameInstance>(World->GetGameInstance());
}

USavesSubsystem* UMageTowerFunctionLibrary::GetSavesSubsystem(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;

	const UWorld* World = WorldContextObject->GetWorld();
	if (!World) return nullptr;

	UGameInstance* GameInstance = Cast<UGameInstance>(World->GetGameInstance());
	if (!GameInstance) return nullptr;

	return GameInstance->GetSubsystem<USavesSubsystem>();
}
