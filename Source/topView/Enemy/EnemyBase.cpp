// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "ConstructorHelpers.h"
#include "Character/Operator.h"
#include "Enemy/EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"



// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_Body(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));

	if (SK_Body.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Body.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance>Anim_Class(TEXT("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C'"));

	if (Anim_Class.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(Anim_Class.Class);
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88.0f), FRotator(0, -90, 0));

	AIControllerClass = AEnemyAIController::StaticClass();

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT_Enemy(TEXT("BehaviorTree'/Game/Blueprint/Enemy/AI/BT_Enemy.BT_Enemy'"));

	if (BT_Enemy.Succeeded())
	{
		BehaviorTree = BT_Enemy.Object;
	}

	CurrentState = EEnemyState::Normal;


}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentHP = MaxHP;
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (CurrentHP <= 0)
	{
		return 0;
	}

	CurrentHP -= DamageAmount;
	if (CurrentHP <= 0)
	{
		CurrentState = EEnemyState::Dead;
		AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());

		if (AIController)
		{
			AIController->BBComponent->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)CurrentState);
		}
	
		AOperator* Char = Cast<AOperator>(DamageCauser);
		
		FVector ImpactVector = Char->DeathImpactVector.GetSafeNormal();

		ImpactVector *= ImpactScale;

		UE_LOG(LogClass, Warning, TEXT("%f %f %f"), ImpactVector.X, ImpactVector.Y, ImpactVector.Z);
		GetMesh()->AddForce(ImpactVector);
		
	}

	return 0;
}

