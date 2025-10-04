// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Battle/MTBattleGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Save/SavesSubsystem.h"
#include "Statics/MageTowerFunctionLibrary.h"
#include "Tower/Tower.h"


void AMTBattleGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	Tower = Cast<ATower>(UGameplayStatics::GetActorOfClass(this, ATower::StaticClass()));
	check(Tower);

	StartGame();
}

void AMTBattleGameStateBase::StartGame()
{
	if (CurrentGameStage != EGameStage::None) return;

	CurrentGameStage = EGameStage::InProgress;

	UE_LOG(LogGameState, Log, TEXT("Game started"));

	Tower->OnTowerDestroyedDelegate.AddDynamic(this, &ThisClass::OnTowerDestroyed);

	OnGameStartedDelegate.Broadcast();
}

void AMTBattleGameStateBase::FinishGame(EGameFinishedReason InReason)
{
	CurrentGameStage = EGameStage::Finished;
	
	UE_LOG(LogGameState, Log, TEXT("Game finished, reason: %s"), *UEnum::GetValueAsString(InReason));

	if (InReason != EGameFinishedReason::Exit)
	{
		USavesSubsystem* SavesSubsystem = UMageTowerFunctionLibrary::GetSavesSubsystem(this);
		check(SavesSubsystem);
		SavesSubsystem->SaveGame();
		SavesSubsystem->UnRegisterSaveableObject(this);
	}
	
	OnGameFinishedDelegate.Broadcast(InReason);
}

void AMTBattleGameStateBase::OnTowerDestroyed(ATower* InTower)
{
	FinishGame(EGameFinishedReason::Lose);
}
