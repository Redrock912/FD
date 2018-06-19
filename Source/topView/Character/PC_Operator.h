// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_Operator.generated.h"

/**
 * 
 */
UCLASS()
class TOPVIEW_API APC_Operator : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	
	UFUNCTION(Server, Reliable, WithValidation)
	void C2S_DestroyItem(AActor* DestroyItem);
	bool C2S_DestroyItem_Validate(AActor* DestroyItem);
	void C2S_DestroyItem_Implementation(AActor* DestroyItem);
};
