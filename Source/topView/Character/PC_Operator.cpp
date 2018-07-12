// Fill out your copyright notice in the Description page of Project Settings.

#include "PC_Operator.h"
#include "ConstructorHelpers.h"
#include "UI/BattleWidgetBase.h"


void APC_Operator::BeginPlay()
{
	//SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;

	InitializeWidget();
}

void APC_Operator::InitializeWidget_Implementation()
{

	// Constructorhelper 에서는 위젯을 읽을수가없다.

	/*static ConstructorHelpers::FClassFinder<UUserWidget>BattleWidget_Class(TEXT("WidgetBlueprint'/Game/Blueprint/Character/UI/OperatorBattleWidget.OperatorBattleWidget_C'"));

	if (BattleWidget_Class.Succeeded())
	{
		BattleWidget = Cast<UBattleWidgetBase>(BattleWidget_Class.Class);

		BattleWidget->AddToViewport();
	}*/

	FStringClassReference BattleWidgetReference(TEXT("WidgetBlueprint'/Game/Blueprint/Character/UI/OperatorBattleWidget.OperatorBattleWidget_C'"));

	if (UClass* MyWidget = BattleWidgetReference.TryLoadClass<UUserWidget>())
	{
		BattleWidget = Cast<UBattleWidgetBase>(CreateWidget<UUserWidget>(this, MyWidget));
		if (BattleWidget && IsLocalController())
		{
			BattleWidget->AddToViewport();
		}
		
	}
}

bool APC_Operator::C2S_DestroyItem_Validate(AActor * DestroyItem)
{
	return true;
}

void APC_Operator::C2S_DestroyItem_Implementation(AActor * DestroyItem)
{
	DestroyItem->Destroy();
}
