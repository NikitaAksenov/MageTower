// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MTPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Spell/SpellComponent.h"


AMTPawn::AMTPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Root);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	SpellComponent = CreateDefaultSubobject<USpellComponent>(TEXT("SpellComponent"));
}

void AMTPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMTPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMTPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

