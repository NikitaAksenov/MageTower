// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"

#include "Components/CapsuleComponent.h"
#include "Components/HealthComponent.h"
#include "Components/WidgetComponent.h"
#include "Core/MTPawn.h"
#include "Core/Battle/MTBattleGameStateBase.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Resources/ResourceDropComponent.h"
#include "Statics/MageTowerFunctionLibrary.h"
#include "Tower/Tower.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	Capsule->SetCanEverAffectNavigation(false);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetCanEverAffectNavigation(false);

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->SetupAttachment(StaticMesh);
	HealthBarWidget->CastShadow = false;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	ResourceDropComponent = CreateDefaultSubobject<UResourceDropComponent>(TEXT("ResourceDropComponent"));

}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnReceivedLethalDamageDelegate.AddDynamic(this, &ThisClass::OnReceivedLethalDamage);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnOverlappedTower(ATower* InTower)
{
	if (!IsValid(InTower)) return;

	InTower->GetHealth()->ApplyDamage(Damage, nullptr, this);

	HealthComponent->ApplyDamage(HealthComponent->GetMaxHealth(), nullptr, this);
}

void AEnemy::OnReceivedLethalDamage(UObject* InCauser, AActor* InInstigator)
{
	if (Cast<AMTPawn>(InInstigator))
	{
		TArray<FResourceInfo> ResourceDrops = ResourceDropComponent->GetResourceDrop();
		for (const FResourceInfo& ResourceDrop : ResourceDrops)
		{
			UMageTowerFunctionLibrary::GetMTBattleGameState(this)->GetResourceContainerRef().Add(ResourceDrop);
		}
	}
	
	Destroy();
}
