// Fill out your copyright notice in the Description page of Project Settings.

#include "DroppedItemGold.h"
#include "Character/Operator.h"
#include "Character/OperatorPS.h"

//void ADroppedItemGold::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//
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
//				PS->gold += 50;
//
//				UE_LOG(LogClass, Warning, TEXT("%d"), PS->gold);
//				Destroy();
//			}
//		}
//	}
//}
