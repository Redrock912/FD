// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_CheckState.h"
#include "Enemy/EnemyBase.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

EBTNodeResult::Type UBTTask_CheckState::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto Enemy = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());

	if (Enemy)
	{
		switch (Enemy->CurrentState)
		{
		case EEnemyState::Dead :
		{
			
			Enemy->CurrentHP = 0;
			Enemy->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Enemy->GetMesh()->SetSimulatePhysics(true);
		}

		}
	}

	return EBTNodeResult::Type();
}
