// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MTGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Tower/Tower.h"


void AMTGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	Tower = Cast<ATower>(UGameplayStatics::GetActorOfClass(this, ATower::StaticClass()));
	check(Tower);

	StartGame();
}

void AMTGameStateBase::StartGame()
{
	if (CurrentGameStage != EGameStage::None) return;

	CurrentGameStage = EGameStage::InProgress;

	UE_LOG(LogGameState, Log, TEXT("Game started"));

	Tower->OnTowerDestroyedDelegate.AddDynamic(this, &ThisClass::AMTGameStateBase::OnTowerDestroyed);

	OnGameStartedDelegate.Broadcast();
}

void AMTGameStateBase::FinishGame(EGameFinishedReason InReason)
{
	CurrentGameStage = EGameStage::Finished;
	
	UE_LOG(LogGameState, Log, TEXT("Game finished, reason: %s"), *UEnum::GetValueAsString(InReason));

	OnGameFinishedDelegate.Broadcast(InReason);
}

void AMTGameStateBase::OnTowerDestroyed(ATower* InTower)
{
	FinishGame(EGameFinishedReason::Lose);
}
