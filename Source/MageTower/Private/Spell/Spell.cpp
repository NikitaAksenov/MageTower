// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell/Spell.h"

#include "Spell/SpellComponent.h"
#include "Spell/SpellTypes.h"


UWorld* USpell::GetWorld() const
{
	return OwningSpellComponent ? OwningSpellComponent->GetWorld() : nullptr;
}

void USpell::Tick(float DeltaTime)
{
	switch (State)
	{
	case ESpellState::Ready:
		{
			if (bActivateOnReady)
			{
				ActivateSpell();
			}
		}
		break;
	case ESpellState::Active:
		break;
	case ESpellState::Cooldown:
		{
			CurrentCooldown += DeltaTime;
			if (CurrentCooldown >= Cooldown)
			{
				ReadySpell();
			}
		}
		break;
	}
}

void USpell::ReadySpell()
{
	UE_LOG(LogSpell, Log, TEXT("%s state is Ready"), *GetName());
	
	State = ESpellState::Ready;

	OnSpellReady();
}

void USpell::ActivateSpell()
{
	if (State != ESpellState::Ready) return;

	UE_LOG(LogSpell, Log, TEXT("%s state is Active"), *GetName());

	State = ESpellState::Active;

	OnSpellActivated();
}

void USpell::CooldownSpell()
{
	if (State != ESpellState::Active) return;
	
	UE_LOG(LogSpell, Log, TEXT("%s state is on Cooldown"), *GetName());

	State = ESpellState::Cooldown;

	CurrentCooldown = 0.f;

	OnSpellCooldown();
}

void USpell::FinishSpell(ESpellFinishReason InReason)
{
	if (State != ESpellState::Active) return;

	UE_LOG(LogSpell, Log, TEXT("%s state is Finished, reason: %s"), *GetName(), *UEnum::GetValueAsString(InReason));

	if (Cooldown >= 0.f)
	{
		CooldownSpell();
	}
	else
	{
		ReadySpell();
	}
}

void USpell::OnSpellReady()
{
}

void USpell::OnSpellActivated()
{
}

void USpell::OnSpellCooldown()
{
}

void USpell::OnSpellFinished(ESpellFinishReason InReason)
{
}

void USpell::RegisterSpell(USpellComponent* InSpellComponent)
{
	if (!InSpellComponent) return;

	if (OwningSpellComponent) return;

	OwningSpellComponent = InSpellComponent;
}
