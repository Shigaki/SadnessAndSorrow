// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AIControllerBase.h"
#include "EnemyAIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class SNS_API AEnemyAIControllerBase : public AAIControllerBase
{
	GENERATED_BODY()

	public:
	AEnemyAIControllerBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void GetActorEyesViewPoint(FVector& out_Location, FRotator& out_Rotation) const override;
};
