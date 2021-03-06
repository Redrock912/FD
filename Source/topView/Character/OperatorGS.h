// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "OperatorGS.generated.h"

/**
 * 
 */
UCLASS()
class TOPVIEW_API AOperatorGS : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, ReplicatedUsing = OnRep_ShowHighScore)
	int HighScore = 0;

	UFUNCTION()
	void OnRep_ShowHighScore();
	
	
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const;
};
