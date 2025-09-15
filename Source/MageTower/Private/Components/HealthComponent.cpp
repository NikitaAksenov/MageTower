// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"


DEFINE_LOG_CATEGORY(LogHealthComponent);


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::UpdateHealth(float InDelta)
{
	SetHealth(CurrentHealth + InDelta);
}

void UHealthComponent::SetHealth(float InValue)
{
	const float OldHealth = CurrentHealth;

	CurrentHealth = FMath::Clamp(InValue, 0.0f, MaxHealth);

	OnHealthChanged(OldHealth, CurrentHealth);

	if (IsHealthDepleted())
	{
		OnHealthDepleted();
	}
}

bool UHealthComponent::IsHealthDepleted() const
{
	return FMath::IsNearlyZero(CurrentHealth);
}

bool UHealthComponent::IsFullHealth() const
{
	return FMath::IsNearlyEqual(CurrentHealth, MaxHealth);
}

float UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

bool UHealthComponent::ApplyDamage(float InDamage, UObject* InInstigator)
{
	if (IsHealthDepleted()) return false;

	UE_LOG(LogHealthComponent, Log, TEXT("%s received %.2f damage from %s"), *GetOwner()->GetName(), InDamage, InInstigator ? *InInstigator->GetName() : TEXT("unknown"));

	UpdateHealth(-InDamage);

	return IsHealthDepleted();
}

void UHealthComponent::OnHealthChanged(float InOldHealth, float InNewHealth)
{
	UE_LOG(LogHealthComponent, Log, TEXT("%s changed health %.2f -> %.2f"), *GetOwner()->GetName(), InOldHealth, InNewHealth);

	OnHealthChangedDelegate.Broadcast(InOldHealth, InNewHealth);
}

void UHealthComponent::OnHealthDepleted()
{
	UE_LOG(LogHealthComponent, Log, TEXT("%s health depleted"), *GetOwner()->GetName());

	OnHealthDepletedDelegate.Broadcast();
}
