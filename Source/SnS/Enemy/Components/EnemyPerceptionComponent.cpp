// Fill out your copyright notice in the Description page of Project Settings.


#include "Sns/Enemy/Components/EnemyPerceptionComponent.h"

#include "AIController.h"
#include "Perception/AISenseConfig_Sight.h"

UEnemyPerceptionComponent::UEnemyPerceptionComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxAgroDistance = 800;
	MaxPerceptionDistance = 500;
	
	UAISenseConfig_Sight* SightConfig = NewObject<UAISenseConfig_Sight>();
	SightConfig->SightRadius = MaxPerceptionDistance;
	SightConfig->LoseSightRadius = MaxAgroDistance;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	ConfigureSense(*SightConfig);
}

void UEnemyPerceptionComponent::BeginPlay()
{
	Super::BeginPlay();
	this->OnTargetPerceptionUpdated.AddDynamic(this, &UEnemyPerceptionComponent::OnTargetPerceptionChanged);
}

void UEnemyPerceptionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	if(AgroTarget)
	{
		const AAIController* AIController = Cast<AAIController>(GetOwner());
		APawn* Pawn = AIController->GetPawn();
		const FVector OurLocation = Pawn->GetActorLocation();
		const FVector PlayerLocation = AgroTarget->GetActorLocation();
		const FVector LookingVector = PlayerLocation - OurLocation;

		if(LookingVector.Size() > MaxAgroDistance)
		{
			SetAgroTarget(nullptr);
			return;
		} 
		
		Pawn->SetActorRotation(LookingVector.Rotation());
	}
}

void UEnemyPerceptionComponent::SetAgroTarget(AActor* NewAgroTarget)
{
	if(NewAgroTarget && !NewAgroTarget->Tags.Contains(TEXT("Player")))
	{
		return;
	}
	
	AgroTarget = NewAgroTarget;
}

void UEnemyPerceptionComponent::SetMaxPerceptionDistance(float NewMaxPerceptionDistance)
{
	MaxPerceptionDistance = NewMaxPerceptionDistance;
	for (int i = 0; i < SensesConfig.Num(); ++i)
	{
		UAISenseConfig* SenseConfig = SensesConfig[i];
		if(SenseConfig->GetClass() == UAISenseConfig_Sight::StaticClass())
		{
			UAISenseConfig_Sight* Sight = Cast<UAISenseConfig_Sight>(SenseConfig);
			Sight->SightRadius = NewMaxPerceptionDistance;
			ConfigureSense(*Sight);
		}
	}
}

void UEnemyPerceptionComponent::OnTargetPerceptionChanged(AActor* Actor, FAIStimulus Stimulus)
{
	UAISenseConfig* SenseConfig = GetSenseConfig(Stimulus.Type);

	if(Stimulus.WasSuccessfullySensed() && SenseConfig->GetClass() == UAISense_Sight::StaticClass())
	{
		SetAgroTarget(Actor);
	}
}
