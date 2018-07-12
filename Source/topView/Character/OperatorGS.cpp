// Fill out your copyright notice in the Description page of Project Settings.

#include "OperatorGS.h"
#include "PC_Operator.h"
#include "Kismet/GameplayStatics.h"
#include "ui/BattleWidgetBase.h"
#include "Components/TextBlock.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"

AOperatorGS::AOperatorGS()
{
	SetReplicates(true);
}

void AOperatorGS::OnRep_ShowHighScore()
{
	
	auto PC = Cast<APC_Operator>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	// UI 업데이트 작업
	if (PC)
	{
		PC->BattleWidget->HighScore->SetText(FText::AsNumber(HighScore));
	}
}

void AOperatorGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOperatorGS, HighScore);
}
