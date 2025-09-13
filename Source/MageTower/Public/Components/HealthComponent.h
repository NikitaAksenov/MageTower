// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "HealthComponent.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogHealthComponent, Log, All);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedDelegate, float, OldHealth, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthDepletedDelegate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGETOWER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	float MaxHealth = 100.f;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Runtime")
	float CurrentHealth = 0.f;

protected:
	UFUNCTION(BlueprintCallable, Category = "Health")
	void UpdateHealth(float InDelta);
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetHealth(float InValue);

public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsHealthDepleted() const;
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsFullHealth() const;
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	bool ApplyDamage(float InDamage, UObject* InInstigator);

public:
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChangedDelegate OnHealthChangedDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthDepletedDelegate OnHealthDepletedDelegate;

protected:
	void OnHealthChanged(float InOldHealth, float InNewHealth);
	void OnHealthDepleted();
};
