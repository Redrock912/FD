// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"


UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Normal		UMETA(Display = "Normal"),
	Chase		UMETA(Display = "Chase"),
	Attack		UMETA(Display = "Attack"),
	Dead		UMETA(Display = "Dead")
};

UCLASS()
class TOPVIEW_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	EEnemyState CurrentState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* BehaviorTree;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ImpactScale = 5000000.0f;


	float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);

};
