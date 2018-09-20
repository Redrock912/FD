// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleWidgetBase.h"
#include "Components/ScrollBox.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Character/Operator.h"

void UBattleWidgetBase::NativeConstruct()
{
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	HighScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("HighScore")));
	Info = Cast<UScrollBox>(GetWidgetFromName(TEXT("Info")));

}

void UBattleWidgetBase::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	// HP percent tick
	auto Char = Cast<AOperator>(GetOwningPlayerPawn());
	if (Char)
	{
		HPBar->SetPercent(Char->CurrentHP / Char->MaxHP);

	}
}
