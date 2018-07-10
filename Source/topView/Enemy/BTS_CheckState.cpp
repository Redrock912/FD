// Fill out your copyright notice in the Description page of Project Settings.

#include "BTS_CheckState.h"
#include "Enemy/EnemyBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Enemy/EnemyAIController.h"
#include "Character/Operator.h"


void UBTS_CheckState::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	auto Enemy = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());

	if (Enemy)
	{
		switch (Enemy->CurrentState)
		{
		case EEnemyState::Attack:
		{
			
			break;
		}
		case EEnemyState::Chase:
		{
			break;
		}
		case EEnemyState::Dead:
		{
			break;
		}
		case EEnemyState::Normal:
		{
			break;
		}
		}
	}
}
