// Fill out your copyright notice in the Description page of Project Settings.

#include "DroppedItemHealth.h"
#include "Character/Operator.h"
#include "Character/OperatorPS.h"


//void ADroppedItemHealth::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
//	if (OtherActor->ActorHasTag(TEXT("Player")))
//	{
//		auto Player = Cast<AOperator>(OtherActor);
//
//		if (Player)
//		{
//			auto PS = Cast<AOperatorPS>(Player->PlayerState);
//
//			if (PS)
//			{
//				
//				PS->CurrentHP = FMath::Clamp(PS->CurrentHP + 20.0f, 0.0f, PS->MaxHP);
//			}
//		}
//	}
//}
