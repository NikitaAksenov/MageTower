// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ResourceTypes.h"

#include "ResourceDropComponent.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogResourceDropComponent, Log, All);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGETOWER_API UResourceDropComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UResourceDropComponent();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Resource|Drop")
	TArray<FResourceDropInfo> ResourceDropInfos;

public:
	UFUNCTION(BlueprintCallable, Category = "Resource|Drop")
	TArray<FResourceInfo> GetResourceDrop() const;
};
