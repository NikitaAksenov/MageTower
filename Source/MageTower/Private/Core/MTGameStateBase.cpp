// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MTGameStateBase.h"

#include "Save/MTSaveGame.h"
#include "Save/SavesSubsystem.h"
#include "Statics/MageTowerFunctionLibrary.h"


AMTGameStateBase::AMTGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMTGameStateBase::HandleSave(UMTSaveGame* InSaveGame)
{
	InSaveGame->ResourceContainer = ResourceContainer;
}

void AMTGameStateBase::HandleLoad(UMTSaveGame* InSaveGame)
{
	ResourceContainer = InSaveGame->ResourceContainer;
}

void AMTGameStateBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GetWorld()->IsGameWorld())
	{
		USavesSubsystem* SavesSubsystem = UMageTowerFunctionLibrary::GetSavesSubsystem(this);
		check(SavesSubsystem);
		
		SavesSubsystem->RegisterSaveableObject(this);
	}
}

void AMTGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	USavesSubsystem* SavesSubsystem = UMageTowerFunctionLibrary::GetSavesSubsystem(this);
	check(SavesSubsystem);
	
	SavesSubsystem->LoadGame();
}

void AMTGameStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Orange, ResourceContainer.GetDebugString());
}
