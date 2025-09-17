// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/ResourceTypes.h"


DEFINE_LOG_CATEGORY(LogResource);

UE_DISABLE_OPTIMIZATION
FResourceContainer::FResourceContainer()
{
}

FResourceContainer::FResourceContainer(const FResourceContainer& InResourceContainer)
{
	for (const TTuple<FGameplayTag, FResourceInfo>& Data : InResourceContainer.Resources)
	{
		Resources.Add(Data.Key, Data.Value);
	}
}

void FResourceContainer::Add(const FGameplayTag& InResourceTypeTag, int32 InAmount)
{
	UE_LOG(LogResource, Log, TEXT("Adding resource %s [%d]"), *InResourceTypeTag.ToString(), InAmount);

	if (FResourceInfo* ResourceInfo = Resources.Find(InResourceTypeTag))
	{
		ResourceInfo->Amount += InAmount;
	}
	else
	{
		Resources.Add(InResourceTypeTag, FResourceInfo(InResourceTypeTag, InAmount));
	}
}

void FResourceContainer::Add(const FResourceInfo& InResourceInfo)
{
	Add(InResourceInfo.ResourceTypeTag, InResourceInfo.Amount);
}

void FResourceContainer::Add(const FResourceContainer& InResourceContainer)
{
	for (const auto& ResourceData : InResourceContainer.Resources)
	{
		FResourceInfo ResourceInfo = ResourceData.Value;
		Add(ResourceInfo);
	}
}
UE_ENABLE_OPTIMIZATION