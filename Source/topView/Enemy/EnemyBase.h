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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	float CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ImpactScale = 50000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TileX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TileY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot", Replicated)
	TSubclassOf<class ADroppedItemBase> Loot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot", Replicated)
	class ADroppedItemBase* LootItem;

	float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);
	
	UFUNCTION(BlueprintCallable)
	void SetTarget(AActor* Char);

	UFUNCTION(NetMulticast, Reliable)
	void S2A_SetPosition(FTransform Transform);
	void S2A_SetPosition_Implementation(FTransform Transform);


	UFUNCTION(BlueprintCallable,NetMulticast, Reliable)
	void S2C_OnDead(AActor* DamageCauser);
	void S2C_OnDead_Implementation(AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable)
	void C2S_OnDead(AActor* DamageCauser);
	bool C2S_OnDead_Validate(AActor* DamageCauser);
	void C2S_OnDead_Implementation(AActor* DamageCauser);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
