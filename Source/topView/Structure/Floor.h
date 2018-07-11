// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Floor.generated.h"

/**
 * 
 */
UCLASS()
class TOPVIEW_API AFloor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:

	AFloor();

	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* Box;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Tile")
	int TileX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	int TileY;
	

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
