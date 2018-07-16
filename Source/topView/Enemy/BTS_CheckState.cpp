// Fill out your copyright notice in the Description page of Project Settings.

#include "BTS_CheckState.h"
#include "Enemy/EnemyBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Enemy/EnemyAIController.h"
#include "Character/Operator.h"
#include "Character/OperatorPS.h"


void UBTS_CheckState::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{

	//UE_LOG(LogClass, Warning, TEXT("AI Working"));
	auto Enemy = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	auto Player = Cast<AOperator>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));

	if (Enemy)
	{
		switch (Enemy->CurrentState)
		{

		case EEnemyState::Chase:
		{
			if (Player)
			{
				auto PS = Cast<AOperatorPS>(Player->PlayerState);
				if (PS)
				{
					if (!(PS->CurrentTileX == Enemy->TileX && PS->CurrentTileY == Enemy->TileY))
					{
						Enemy->CurrentState = EEnemyState::Normal;
						OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)Enemy->CurrentState);
					}
				}
				
			}
			
		}
		break;
		case EEnemyState::Normal:
		{
			
			UE_LOG(LogClass, Warning, TEXT("AI Working inside Normal"));

			if (Player)
			{

				auto PS = Cast<AOperatorPS>(Player->PlayerState);
				if (PS)
				{
					if (PS->CurrentTileX == Enemy->TileX && PS->CurrentTileY == Enemy->TileY)
					{
						Enemy->CurrentState = EEnemyState::Chase;
						OwnerComp.GetBlackboardComponent()->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)Enemy->CurrentState);
					}
				}

			}
		}
		break;
		}
	}
}
