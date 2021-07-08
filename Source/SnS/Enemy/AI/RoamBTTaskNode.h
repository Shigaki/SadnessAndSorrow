// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SnS/Enemy/Components/RoamingComponent.h"

#include "RoamBTTaskNode.generated.h"

struct URoamBTTask
{
	bool HasLocation;
	FNavLocation RandomLocation;
};

/**
 * 
 */
UCLASS()
class SNS_API URoamBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

	public:
	URoamBTTaskNode();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	APawn* GetPawn(UBehaviorTreeComponent& OwnerComp);
	URoamingComponent* GetRoamingComponent(UBehaviorTreeComponent& OwnerComp);

	virtual uint16 GetInstanceMemorySize() const override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
