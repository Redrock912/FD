// Fill out your copyright notice in the Description page of Project Settings.

#include "Floor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Character/Operator.h"
#include "Character/OperatorPS.h"



AFloor::AFloor()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(GetStaticMeshComponent());


}

void AFloor::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AFloor::OnBeginOverlap);
}

void AFloor::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		auto Char = Cast<AOperator>(OtherActor);
		if (Char)
		{
			auto PS = Cast<AOperatorPS>(Char->PlayerState);
			if (PS)
			{
				// network ??
				PS->CurrentTileX = TileX;
				PS->CurrentTileY = TileY;
			}
		}

	}

}
