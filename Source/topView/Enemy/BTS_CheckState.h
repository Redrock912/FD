// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_CheckState.generated.h"

/**
 * 
 */
UCLASS()
class TOPVIEW_API UBTS_CheckState : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};
