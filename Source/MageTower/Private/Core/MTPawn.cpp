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
	SpringArm->TargetArmLength = 1000.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetWorldRotation(FRotator(-90.f, 0.f, 0.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetProjectionMode(ECameraProjectionMode::Type::Orthographic);
	Camera->OrthoWidth = 7680.f;
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

