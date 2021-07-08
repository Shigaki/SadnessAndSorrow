// Fill out your copyright notice in the Description page of Project Settings.


#include "Sns/Enemy/AI/RoamBTTaskNode.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "SnS/Enemy/Components/RoamingComponent.h"

URoamBTTaskNode::URoamBTTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type URoamBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	URoamingComponent* RoamingComponent = GetRoamingComponent(OwnerComp);
	if(!RoamingComponent)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(OwnerComp.GetWorld());

	FNavLocation RandomLocation;
	if(NavigationSystem->GetRandomReachablePointInRadius(RoamingComponent->RoamingCenterPoint, RoamingComponent->RoamingAreaRadius, RandomLocation))
	{
		AAIController* AIController = Cast<AAIController>(OwnerComp.GetOwner());
		EPathFollowingRequestResult::Type MoveResult = AIController->MoveToLocation(RandomLocation);

		if(MoveResult == EPathFollowingRequestResult::Failed)
		{
			return EBTNodeResult::Failed;
		}

		if(MoveResult == EPathFollowingRequestResult::AlreadyAtGoal)
		{
			return EBTNodeResult::Succeeded;
		}

		URoamBTTask* Task = CastInstanceNodeMemory<URoamBTTask>(NodeMemory);
		Task->HasLocation = true;
		Task->RandomLocation = RandomLocation;
		
		return EBTNodeResult::InProgress;
		
	}

	return EBTNodeResult::Failed;
	
}


APawn* URoamBTTaskNode::GetPawn(UBehaviorTreeComponent& OwnerComp)
{
	AAIController* AIController = Cast<AAIController>(OwnerComp.GetOwner());
	if(!AIController)
	{
		return nullptr;
	}

	APawn* Pawn = AIController->GetPawn();
	if(!Pawn)
	{
		return nullptr;
	}

	return Pawn;
}


URoamingComponent* URoamBTTaskNode::GetRoamingComponent(UBehaviorTreeComponent& OwnerComp)
{
	return Cast<URoamingComponent>(GetPawn(OwnerComp)->GetComponentByClass(URoamingComponent::StaticClass()));
}

uint16 URoamBTTaskNode::GetInstanceMemorySize() const
{
	return sizeof(URoamBTTask);
}

void URoamBTTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	URoamBTTask* Task = CastInstanceNodeMemory<URoamBTTask>(NodeMemory);
	if(Task->HasLocation)
	{
		AAIController* AIController = Cast<AAIController>(OwnerComp.GetOwner());
		EPathFollowingRequestResult::Type MoveResult = AIController->MoveToLocation(Task->RandomLocation);
		if(MoveResult != EPathFollowingRequestResult::RequestSuccessful)
		{
			Task->HasLocation = false;
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}
