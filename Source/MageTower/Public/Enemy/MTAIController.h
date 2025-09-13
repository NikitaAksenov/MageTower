// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "MTAIController.generated.h"


class ATower;


/**
 * 
 */
UCLASS()
class MAGETOWER_API AMTAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Runtime")
	TWeakObjectPtr<ATower> Tower;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	bool bLifecycleStarted = false;

protected:
	void StartLifecycle();
};
