// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOPVIEW_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	
	AEnemyAIController();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBehaviorTreeComponent* BTComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBlackboardComponent* BBComponent;

	//UFUNCTION()
	//virtual void Possess(APawn* InPawn) override;
	
	
	
};
