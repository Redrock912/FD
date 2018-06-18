// Fill out your copyright notice in the Description page of Project Settings.

#include "PC_Operator.h"


bool APC_Operator::C2S_DestroyItem_Validate(AActor * DestroyItem)
{
	return true;
}

void APC_Operator::C2S_DestroyItem_Implementation(AActor * DestroyItem)
{
	DestroyItem->Destroy();
}

