// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemySpawnSubsystem.h"

#include "Core/Battle/MTBattleGameModeBase.h"
#include "Core/Battle/MTBattleGameStateBase.h"
#include "Enemy/Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Statics/MageTowerFunctionLibrary.h"
#include "Tower/Tower.h"


DEFINE_LOG_CATEGORY(LogEnemySpawnSubsystem);


void UEnemySpawnSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	const AMTBattleGameModeBase* GameMode = UMageTowerFunctionLibrary::GetMTBattleGameMode(this);
	if (!GameMode)
	{
		UE_LOG(LogEnemySpawnSubsystem, Log, TEXT("EnemySwarmSubsystem will not be created, because game mode is not BattleGameMode"));
		return;
	}

	AMTBattleGameStateBase* GameState = UMageTowerFunctionLibrary::GetMTBattleGameState(this);
	check(GameState);
	if (GameState->IsGameInProgress())
	{
		OnGameStarted();
	}
	else
	{
		GameState->OnGameStartedDelegate.AddDynamic(this, &ThisClass::OnGameStarted);
	}
	GameState->OnGameFinishedDelegate.AddDynamic(this, &ThisClass::OnGameFinished);
}

void UEnemySpawnSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSpawning)
	{
		ProcessSpawning(DeltaTime);
	}
}

void UEnemySpawnSubsystem::StartSpawning(const FEnemySpawnSettings& InSpawnSettings)
{
	if (bSpawning) return;

	UE_LOG(LogEnemySpawnSubsystem, Log, TEXT("Start spawning"));

	bSpawning = true;

	SpawnRuntimeData = MakeShared<FEnemySpawnRuntimeData>(FEnemySpawnRuntimeData(InSpawnSettings));
}

void UEnemySpawnSubsystem::StopSpawning()
{
	if (!bSpawning) return;

	UE_LOG(LogEnemySpawnSubsystem, Log, TEXT("Stop spawning"));
	
	bSpawning = false;

	SpawnRuntimeData.Reset();
}

void UEnemySpawnSubsystem::OnGameStarted()
{
	AMTBattleGameModeBase* GameMode = UMageTowerFunctionLibrary::GetMTBattleGameMode(this);
	check(GameMode);
	
	StartSpawning(GameMode->GetDefaultSpawnSettings());
}

void UEnemySpawnSubsystem::OnGameFinished(EGameFinishedReason InReason)
{
	StopSpawning();
}

void UEnemySpawnSubsystem::ProcessSpawning(float DeltaTime)
{
	SpawnRuntimeData->DurationSinceLastSpawn += DeltaTime;
	const bool bTimeToSpawn = SpawnRuntimeData->DurationSinceLastSpawn >= SpawnRuntimeData->SpawnSettings.SpawnRate;
	if (bTimeToSpawn)
	{
		const FVector SpawnLocation = FindSpawnLocation();
		
		AEnemy* SpawnedEnemy = SpawnEnemy(SpawnRuntimeData->GetEnemyClass(), SpawnLocation);
		
		SpawnRuntimeData->DurationSinceLastSpawn = 0.f;
	}
}

AEnemy* UEnemySpawnSubsystem::SpawnEnemy(const TSubclassOf<AEnemy>& InEnemyClass, const FVector& InLocation) const
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	return GetWorld()->SpawnActor<AEnemy>(InEnemyClass, InLocation, FRotator::ZeroRotator, SpawnParams);
}

FVector UEnemySpawnSubsystem::FindSpawnLocation() const
{
	const ATower* Tower = Cast<ATower>(UGameplayStatics::GetActorOfClass(this, ATower::StaticClass()));

	constexpr float Radius = 2500.f;
	const float RandAngleDeg = FMath::RandRange(0.f, 360.f);
	const float X = Radius * FMath::Cos(RandAngleDeg);
	const float Y = Radius * FMath::Sin(RandAngleDeg);
	
	return FVector(X, Y, Tower->GetActorLocation().Z);
}
