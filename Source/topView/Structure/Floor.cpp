// Fill out your copyright notice in the Description page of Project Settings.

#include "Floor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/Operator.h"
#include "Character/OperatorPS.h"
#include "Character/PC_Operator.h"
#include "Enemy/EnemyBase.h"	
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
	// 적 리스트 저장
	if (OtherActor->ActorHasTag(TEXT("Enemy")))
	{

		auto Enemy = Cast<AEnemyBase>(OtherActor);
		if (Enemy)
		{
			// 적도 위치 지정
			Enemy->TileX = TileX;
			Enemy->TileY = TileY;

			EnemyList.Add(Enemy);
		}
		

	}

	// 플레이어가 발판을 밟을 시
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
			
			UE_LOG(LogClass, Warning, TEXT("QP2"));
			for (auto Enemies : EnemyList)
			{
				UE_LOG(LogClass, Warning, TEXT("QP"));
				Enemies->SetTarget(Char);
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
