// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Operator.generated.h"


UCLASS()
class TOPVIEW_API AOperator : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOperator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetDirection();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	void Interact();
	UFUNCTION()
	void MoveRight(float Value);
	UFUNCTION()
	void MoveForward(float Value);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void OnShot();

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION(BlueprintCallable)
	void OnDead(FVector Impact);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharInfo")
		float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharInfo")
		float CurrentHP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharInfo")
		float AttackRange = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharInfo")
	float RecoilTime = 0.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharInfo")
	FTimerHandle ShootTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector DeathImpactVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsShooting = false;

	TArray<class AStructureBase*> InteractableList;

	UFUNCTION(BlueprintCallable)
	void AddInteractableList(class AStructureBase* Sturcture);

	UFUNCTION(BlueprintCallable)
	void RemoveInteractableList(class AStructureBase* Sturcture);

	UFUNCTION()
	void ConsumeItem(AItemBase* Item);

	UFUNCTION()
	void EquipItem(AItemBase* Item);

};
