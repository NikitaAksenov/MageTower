// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "ResourceTypes.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogResource, Log, All);


USTRUCT(BlueprintType)
struct FResourceInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Resource.Type"))
	FGameplayTag ResourceTypeTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount;
};


USTRUCT(BlueprintType)
struct FResourceDropInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Resource.Type"))
	FResourceInfo ResourceInfo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0.f, ClampMin = 0.f, UIMax = 1.f, ClampMax = 1.f))
	float DropChance;
};

USTRUCT(BlueprintType)
struct FResourceContainer
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleInstanceOnly)
	TMap<FGameplayTag, FResourceInfo> Resources;

public:
	void Add(const FGameplayTag& InResourceTypeTag, int32 InAmount);
	void Add(const FResourceInfo& InResourceInfo);
};
