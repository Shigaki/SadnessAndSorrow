// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIControllerBase.h"

#include "Components/EnemyPerceptionComponent.h"

AEnemyAIControllerBase::AEnemyAIControllerBase(const FObjectInitializer& ObjectInitializer)
{
	UEnemyPerceptionComponent* EnemyPerceptionComponent = CreateDefaultSubobject<UEnemyPerceptionComponent>("EnemyPerception");
	
	SetPerceptionComponent(*EnemyPerceptionComponent);
}

void AEnemyAIControllerBase::GetActorEyesViewPoint(FVector& out_Location, FRotator& out_Rotation) const {
	APawn* ControlledPawn = GetPawn();
	if(!ControlledPawn) { return; }
	out_Location = ControlledPawn->GetActorLocation();
	out_Rotation = ControlledPawn->GetActorRotation();
}