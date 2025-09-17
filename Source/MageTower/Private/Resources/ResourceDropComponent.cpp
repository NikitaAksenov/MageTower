// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/ResourceDropComponent.h"


DEFINE_LOG_CATEGORY(LogResourceDropComponent);


UResourceDropComponent::UResourceDropComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UResourceDropComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

TArray<FResourceInfo> UResourceDropComponent::GetResourceDrop() const
{
	TArray<FResourceInfo> ResourceDrops;

	for (const FResourceDropInfo& ResourceDropInfo : ResourceDropInfos)
	{
		const float RandValue = FMath::FRandRange(0.f, 1.f);
		const float DropChance = ResourceDropInfo.DropChance;
		const bool bShouldDrop = DropChance == 1.f || RandValue < DropChance;
		
		UE_LOG(LogResourceDropComponent, Display, TEXT("Value [%.2f] / Chance: [%.2f] / ShouldDrop: %d"),
			RandValue, DropChance, bShouldDrop);
		
		if (bShouldDrop)
		{
			ResourceDrops.Add(ResourceDropInfo.ResourceInfo);
		}
	}
	
	return ResourceDrops;
}

