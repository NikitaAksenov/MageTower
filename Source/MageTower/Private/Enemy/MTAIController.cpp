// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/MTAIController.h"

#include "Core/MTGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Statics/MageTowerFunctionLibrary.h"
#include "Tower/Tower.h"


DEFINE_LOG_CATEGORY(LogEnemy);


void AMTAIController::BeginPlay()
{
	Super::BeginPlay();

	GameState = UMageTowerFunctionLibrary::GetMTGameState(this);
	check(GameState);
	GameState->OnGameStartedDelegate.AddDynamic(this, &ThisClass::AMTAIController::OnGameStarted);
	GameState->OnGameFinishedDelegate.AddDynamic(this, &ThisClass::AMTAIController::OnGameFinished);
}

void AMTAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (GameState->IsGameInProgress())
	{
		StartLifecycle();
	}
}

void AMTAIController::StartLifecycle()
{
	check(GetPawn());
	
	if (bLifecycleStarted) return;

	UE_LOG(LogEnemy, Log, TEXT("%s lifecycle started"), *GetPawn()->GetName());

	bLifecycleStarted = true;

	Tower = Cast<ATower>(UGameplayStatics::GetActorOfClass(this, ATower::StaticClass()));
	if (Tower.IsValid())
	{
		EPathFollowingRequestResult::Type Result = MoveToActor(Tower.Get());
	}
}

void AMTAIController::StopLifecycle()
{
	check(GetPawn());

	if (!bLifecycleStarted) return;

	UE_LOG(LogEnemy, Log, TEXT("%s lifecycle stopped"), *GetPawn()->GetName());

	bLifecycleStarted = false;

	StopMovement();	
}

void AMTAIController::OnGameStarted()
{
	if (GetPawn())
	{
		StartLifecycle();
	}
}

void AMTAIController::OnGameFinished(EGameFinishedReason InReason)
{
	StopLifecycle();
}
