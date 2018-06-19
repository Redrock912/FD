// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAniminstance.h"
#include "Character/Operator.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAniminstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Char = Cast<AOperator>(TryGetPawnOwner());

	if (Char&&Char->IsValidLowLevel())
	{
		Speed = Char->GetCharacterMovement()->Velocity.Size();
		Direction = CalculateDirection(Char->GetCharacterMovement()->Velocity, Char->GetActorRotation());
	}
}
