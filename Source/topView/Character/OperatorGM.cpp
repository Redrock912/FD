// Fill out your copyright notice in the Description page of Project Settings.

#include "OperatorGM.h"
#include "OperatorGS.h"
#include "PC_Operator.h"
#include "OperatorPS.h"

void AOperatorGM::BeginPlay()
{
	Super::BeginPlay();

	
}

void AOperatorGM::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	UE_LOG(LogClass, Warning, TEXT("%d"), count);
	count += 1;
	auto PC = Cast<APC_Operator>(NewPlayer);
	if (PC)
	{
		auto PS = Cast<AOperatorPS>(PC->PlayerState);


		// HP,gold init
		if (PS)
		{
			PS->CurrentHP = PS->MaxHP;
			PS->gold = 0;
		}
	}
	
}
