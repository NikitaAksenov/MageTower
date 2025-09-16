// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Tower.generated.h"


class UHealthComponent;
class USphereComponent;
class UWidgetComponent;


DECLARE_LOG_CATEGORY_EXTERN(LogTower, Log, All);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTowerEvent, ATower*, Tower);


UCLASS()
class MAGETOWER_API ATower : public AActor
{
	GENERATED_BODY()
	
public:
	ATower();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> EnemyOverlapSphere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UWidgetComponent> HealthBarWidget;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UHealthComponent> Health;

public:
	UPROPERTY(BlueprintAssignable, Category = "Tower")
	FTowerEvent OnTowerDestroyedDelegate;

protected:
	UFUNCTION()
	void OnEnemySphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTowerDestroyed();

public:
	UFUNCTION(BlueprintCallable, Category = "Tower")
	FORCEINLINE UHealthComponent* GetHealth() { return Health; }
};
