// Fill out your copyright notice in the Description page of Project Settings.

#include "Floor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/Operator.h"
#include "Character/OperatorPS.h"
#include "Character/PC_Operator.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"



AFloor::AFloor()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(GetStaticMeshComponent());

	// Box Setup
	Box->SetBoxExtent(FVector(500.0f, 500.0f, 32.0f));


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetStaticMeshComponent());

	// Camera Setup
	Camera->SetRelativeLocation(FVector(-400.0f, 0.0f, 800.0f));
	Camera->SetRelativeRotation(FRotator(-70.0f, 0.0f, 0.0f));

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
		if (Char->IsLocallyControlled())
		{
			auto PS = Cast<AOperatorPS>(Char->PlayerState);
			if (PS)
			{
				// network ??
				PS->CurrentTileX = TileX;
				PS->CurrentTileY = TileY;
			}

			auto PC = Cast<APC_Operator>(Char->GetController());
			
			if (PC)
			{
				
				PC->SetViewTargetWithBlend(this);
			}
			
		}

	}
}

void AFloor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFloor, TileX);
	DOREPLIFETIME(AFloor, TileY);
}
