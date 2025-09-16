// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "MageTowerFunctionLibrary.generated.h"


class AMTGameModeBase;
class AMTGameStateBase;


/**
 * 
 */
UCLASS()
class MAGETOWER_API UMageTowerFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MageTower")
	static AMTGameStateBase* GetMTGameState(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "MageTower")
	static AMTGameModeBase* GetMTGameMode(const UObject* WorldContextObject);
};
