// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/Tower.h"

#include "Components/HealthComponent.h"
#include "Components/SphereComponent.h"
#include "Enemy/Enemy.h"


DEFINE_LOG_CATEGORY(LogTower);


ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Root);

	EnemyOverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("EnemyOverlapSphere"));
	EnemyOverlapSphere->SetupAttachment(Root);

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	EnemyOverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnEnemySphereBeginOverlap);

	Health->OnHealthDepletedDelegate.AddDynamic(this, &ThisClass::OnTowerDestroyed);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATower::OnEnemySphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTower, Log, TEXT("Overlapped %s"), *OtherActor->GetName());

	if (AEnemy* Enemy = Cast<AEnemy>(OtherActor))
	{
		Enemy->OnOverlappedTower(this);
	}
}

void ATower::OnTowerDestroyed()
{
	UE_LOG(LogTower, Log, TEXT("Tower destroyed"));

	OnTowerDestroyedDelegate.Broadcast(this);
}
