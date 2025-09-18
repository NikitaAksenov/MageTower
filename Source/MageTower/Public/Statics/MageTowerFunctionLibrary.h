// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "MageTowerFunctionLibrary.generated.h"


class AMTBattleGameModeBase;
class AMTBattleGameStateBase;
class AMTGameModeBase;
class AMTGameStateBase;
class AMTUpgradeGameModeBase;
class AMTUpgradeGameStateBase;

class UMTGameInstance;


/**
 * 
 */
UCLASS()
class MAGETOWER_API UMageTowerFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MageTower|GameState")
	static AMTGameStateBase* GetMTGameState(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "MageTower|GameState")
	static AMTBattleGameStateBase* GetMTBattleGameState(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "MageTower|GameState")
	static AMTUpgradeGameStateBase* GetMTUpgradeGameState(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "MageTower|GameMode")
	static AMTGameModeBase* GetMTGameMode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "MageTower|GameMode")
	static AMTBattleGameModeBase* GetMTBattleGameMode(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "MageTower|GameMode")
	static AMTUpgradeGameModeBase* GetMTUpgradeGameMode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "MageTower|GameInstance")
	static UMTGameInstance* GetMTGameInstance(const UObject* WorldContextObject);
};
