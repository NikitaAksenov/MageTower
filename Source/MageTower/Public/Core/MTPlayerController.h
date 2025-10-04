// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "MTPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class MAGETOWER_API AMTPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMTPlayerController();

public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TObjectPtr<UUserWidget> HUDWidget;
};
