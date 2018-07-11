// Fill out your copyright notice in the Description page of Project Settings.

#include "Pot.h"
#include "ConstructorHelpers.h"
#include "Character/Operator.h"
#include "Character/OperatorPS.h"
#include "Character/OperatorGS.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values
APot::APot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APot::DoSomething(AActor* Player)
{
	auto Char = Cast<AOperator>(Player);
	if (Char)
	{
		auto PS = Cast<AOperatorPS>(Char->PlayerState);
		auto GS = Cast<AOperatorGS>(UGameplayStatics::GetGameState(GetWorld()));
		if (PS)
		{
			int Score = PS->gold;
			PS->gold -= PS->gold;
			PS->Score += Score;
			

			// 현재 최고점수보다 낮을 시 플레이어 스코어랑 변환
			if (GS)
			{

				if (GS->HighScore < PS->Score)
				{
					GS->HighScore = PS->Score;
					if (HasAuthority())
					{
						GS->HighScore = PS->Score;
					}

				}
			}			
		}
	}

}

