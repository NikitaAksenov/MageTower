// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources/ResourceTypes.h"


DEFINE_LOG_CATEGORY(LogResource);


void FResourceContainer::Add(const FGameplayTag& InResourceTypeTag, int32 InAmount)
{
	UE_LOG(LogResource, Log, TEXT("Adding resource %s [%d]"), *InResourceTypeTag.ToString(), InAmount);
	
	Resources.FindOrAdd(InResourceTypeTag).Amount += InAmount;
}

void FResourceContainer::Add(const FResourceInfo& InResourceInfo)
{
	Add(InResourceInfo.ResourceTypeTag, InResourceInfo.Amount);
}
