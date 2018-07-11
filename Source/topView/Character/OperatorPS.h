// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "OperatorPS.generated.h"

/**
 * 
 */
UCLASS()
class TOPVIEW_API AOperatorPS : public APlayerState
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int gold;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MaxHP = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurrentHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int CurrentTileX;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int CurrentTileY;


};
