// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell/Player/Spell_ArcaneBlast.h"

#include "Components/HealthComponent.h"
#include "Core/MTPlayerController.h"
#include "Spell/SpellNativeTags.h"


USpell_ArcaneBlast::USpell_ArcaneBlast()
{
	SpellTag = TAG_Spell_ID_ArcaneBlast;
}

void USpell_ArcaneBlast::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Hit;
	Controller->GetHitResultUnderCursorForObjects(ObjectTypes, false, Hit);
	LocationUnderCursor = Hit.Location;

	DrawDebugCylinder(GetWorld(), LocationUnderCursor, LocationUnderCursor, Radius, 32, FColor::Red, false, DeltaTime * 2.f);

	switch (State) {
	case ESpellState::Ready:
		break;
	case ESpellState::Active:
		break;
	case ESpellState::Cooldown:
		{
			const float Percentage = GetCooldownPercentage();
			DrawDebugCylinder(GetWorld(), LocationUnderCursor, LocationUnderCursor, Radius * Percentage, 32, FColor::Red, false, DeltaTime * 2.f);
		}
		break;
	}
}

void USpell_ArcaneBlast::OnSpellActivated()
{
	Super::OnSpellActivated();

	TArray<FHitResult> Hits;
	GetWorld()->SweepMultiByChannel(Hits, LocationUnderCursor, LocationUnderCursor, FQuat::Identity, DamageCollisionChannel, FCollisionShape::MakeSphere(Radius));
	for (FHitResult& DamageHit : Hits)
	{
		AActor* DamagedActor = DamageHit.GetActor();

		if (UHealthComponent* HealthComponent = DamagedActor->FindComponentByClass<UHealthComponent>())
		{
			HealthComponent->ApplyDamage(Damage, this);
		}
		
		// DrawDebugBox(GetWorld(), DamagedActor->GetActorLocation(), FVector(200.f, 200.f, 0.f), FColor::Red);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, DamagedActor->GetName());
	}

	FinishSpell(ESpellFinishReason::Finished);
}
