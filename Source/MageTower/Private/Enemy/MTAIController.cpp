// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/MTAIController.h"

#include "Kismet/GameplayStatics.h"
#include "Tower/Tower.h"


void AMTAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMTAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	StartLifecycle();
}

void AMTAIController::StartLifecycle()
{
	if (bLifecycleStarted) return;

	bLifecycleStarted = true;

	Tower = Cast<ATower>(UGameplayStatics::GetActorOfClass(this, ATower::StaticClass()));
	if (Tower.IsValid())
	{
		EPathFollowingRequestResult::Type Result = MoveToActor(Tower.Get());
	}
}
