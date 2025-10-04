// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "SaveableInterface.generated.h"


class UMTSaveGame;


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USaveableInterface : public UInterface
{
	GENERATED_BODY()
};


/**
 * 
 */
class MAGETOWER_API ISaveableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void HandleSave(UMTSaveGame* InSaveGame) = 0;
	virtual void HandleLoad(UMTSaveGame* InSaveGame) = 0;
};
