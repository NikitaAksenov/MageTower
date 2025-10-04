// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/ResourceTypes.h"


DEFINE_LOG_CATEGORY(LogResource);


FString FResourceInfo::ToString() const
{
	return ResourceTypeTag.ToString() + " " + FString::FromInt(Amount);
}

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

FString FResourceContainer::GetDebugString() const
{
	FString DebugString;

	if (Resources.IsEmpty())
	{
		return "No resources";
	}

	int Index = 1;
	for (auto& Resource : Resources)
	{
		DebugString += FString::Printf(TEXT("#%d %s\n"), Index++, *Resource.Value.ToString());
	}
	
	return DebugString;
}
