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
	UFUNCTION(Server, WithValidation, Reliable)
	void C2S_SetDirection(FRotator NewRotation);
	bool C2S_SetDirection_Validate(FRotator NewRotation);
	void C2S_SetDirection_Implementation(FRotator NewRotation);

	UFUNCTION(Client, Reliable)
	void S2C_SetDirection(FRotator Rotation);
	void S2C_SetDirection_Implementation(FRotator Rotation);
	
	

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

	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable)
	void C2S_OnShot();
	bool C2S_OnShot_Validate();
	void C2S_OnShot_Implementation();

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION(BlueprintCallable, NetMulticast,Reliable)
	void OnDead(FVector Impact);
	void OnDead_Implementation(FVector Impact);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharInfo")
		float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharInfo" , Replicated)
		float CurrentHP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharInfo")
		float AttackRange = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharInfo")
	float RecoilTime = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	FRotator LookingRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharInfo")
	FTimerHandle ShootTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FVector DeathImpactVector;

	// 로테이션에 쓰려고했다가 틱으로 계속 사용
	//FTimerHandle TimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
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


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
