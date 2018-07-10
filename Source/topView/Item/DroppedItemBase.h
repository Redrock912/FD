// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DroppedItemBase.generated.h"

UCLASS()
class TOPVIEW_API ADroppedItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADroppedItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult &SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ImpactMin = 1000000.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ImpactMax = 2000000.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float MassScale = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* ItemBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* Sphere;
};
