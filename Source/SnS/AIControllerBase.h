// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class SNS_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	void GetActorEyesViewPoint(FVector& out_Location, FRotator& out_Rotation) const override;
	UFUNCTION(BlueprintImplementableEvent, Category = "AICBase")
	void BPGetActorEyesViewPoint(FVector& out_Location, FRotator& out_Rotation) const;
};
