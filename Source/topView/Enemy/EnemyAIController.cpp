// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "Enemy/EnemyBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AEnemyAIController::AEnemyAIController()
{
	BTComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));

	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
}

void AEnemyAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	auto Enemy = Cast<AEnemyBase>(InPawn);

	if (Enemy)
	{
		BBComponent->InitializeBlackboard(*(Enemy->BehaviorTree->BlackboardAsset));

		BTComponent->StartTree(*Enemy->BehaviorTree);
	}
}
