// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAniminstance.generated.h"

/**
 * 
 */
UCLASS()
class TOPVIEW_API UMyAniminstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AnimationInfo")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimationInfo")
	float Direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimationInfo")
	bool bIsShooting = false;
};
