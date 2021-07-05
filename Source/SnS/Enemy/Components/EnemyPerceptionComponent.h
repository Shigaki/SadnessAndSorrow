// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "EnemyPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class SNS_API UEnemyPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

	public:
	UEnemyPerceptionComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	public:
	UPROPERTY(BlueprintReadWrite, BlueprintSetter=SetAgroTarget)
	class AActor* AgroTarget;

	UFUNCTION(BlueprintCallable, BlueprintSetter)
	virtual void SetAgroTarget(class AActor* NewAgroTarget);

	UPROPERTY(BlueprintReadWrite)
	float MaxAgroDistance;
	UPROPERTY(BlueprintReadWrite, BlueprintSetter=SetMaxPerceptionDistance)
	float MaxPerceptionDistance;

	UFUNCTION(BlueprintCallable, BlueprintSetter)
	virtual void SetMaxPerceptionDistance(float NewMaxPerceptionDistance);

	private:
	UFUNCTION(BlueprintCallable)
	virtual void OnTargetPerceptionChanged(AActor* Actor, FAIStimulus Stimulus);
};
