// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/DroppedItemBase.h"
#include "DroppedItemGold.generated.h"

/**
 * 
 */
UCLASS()
class TOPVIEW_API ADroppedItemGold : public ADroppedItemBase
{
	GENERATED_BODY()
	
public:


	UFUNCTION()
		virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult) override;
	
	
};
