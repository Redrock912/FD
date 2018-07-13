// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "ConstructorHelpers.h"
#include "Character/Operator.h"
#include "Enemy/EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Item/DroppedItemBase.h"
#include "UnrealNetwork.h"




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


	static ConstructorHelpers::FObjectFinder<UBlueprint>Loot_Item(TEXT("Blueprint'/Game/Blueprint/Item/BP_DroppedItemGold.BP_DroppedItemGold'"));

	if (Loot_Item.Succeeded())
	{
		Loot = (UClass*)Loot_Item.Object->GeneratedClass;
	}

	//static ConstructorHelpers::FObjectFinder<ADroppedItemBase>Loot_Item2(TEXT("Blueprint'/Game/Blueprint/Item/BP_DroppedItemBase.BP_DroppedItemBase'"));
	//if (Loot_Item2.Succeeded())
	//{
	//	Loot2 = Loot_Item2.Object;
	//}

	bReplicates = true;
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

	auto Char = Cast<AOperator>(DamageCauser);

	CurrentHP -= DamageAmount;
	if (CurrentHP <= 0)
	{

		//if (HasAuthority())
		//{

		//	S2C_OnDead(DamageCauser);
		//}
		//else
		//{
		//	if (IsLocallyControlled())
		//	{
		//		// 클라이언트 상에서 돌려주고, 값을 나중에 서버에 보낸다.
		//		GetCapsuleComponent()->SetWorldRotation(LookingRotation);
		//		C2S_SetDirection(LookingRotation);
		//	}
		//}
		//S2C_OnDead(DamageCauser);
		S2C_OnDead(DamageCauser);
	}

	return 0;
}

void AEnemyBase::S2C_OnDead_Implementation(AActor* DamageCauser)
{
	CurrentState = EEnemyState::Dead;
	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());

	if (AIController)
	{
		AIController->BBComponent->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)CurrentState);
	}

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AOperator* Char = Cast<AOperator>(DamageCauser);

	FVector ImpactVector = Char->DeathImpactVector.GetSafeNormal();

	ImpactVector *= ImpactScale;

	UE_LOG(LogClass, Warning, TEXT("%f %f %f"), ImpactVector.X, ImpactVector.Y, ImpactVector.Z);
	// 먼저 물리작용을 허용해준a다.
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->AddImpulse(ImpactVector);
	//GetMesh()->AddForce(ImpactVector);
	

	// Loot Item, Gold
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	if (Loot)
	{
		UWorld* CurrentWorld = GetWorld();
		if (CurrentWorld)
		{
			CurrentWorld->SpawnActor<ADroppedItemBase>(Loot, GetActorLocation(), GetActorRotation(), SpawnInfo);
		}
	}
	/*UE_LOG(LogClass, Warning, TEXT("%s"), Gold);*/
}

bool AEnemyBase::C2S_OnDead_Validate(AActor * DamageCauser)
{
	return true;
}

void AEnemyBase::C2S_OnDead_Implementation(AActor* DamageCauser)
{
	CurrentState = EEnemyState::Dead;
	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());

	if (AIController)
	{
		AIController->BBComponent->SetValueAsEnum(FName(TEXT("CurrentState")), (uint8)CurrentState);
	}

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AOperator* Char = Cast<AOperator>(DamageCauser);

	FVector ImpactVector = Char->DeathImpactVector.GetSafeNormal();

	ImpactVector *= ImpactScale;

	UE_LOG(LogClass, Warning, TEXT("%f %f %f"), ImpactVector.X, ImpactVector.Y, ImpactVector.Z);
	// 먼저 물리작용을 허용해준a다.
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->AddImpulse(ImpactVector);
	//GetMesh()->AddForce(ImpactVector);


	// Loot Item, Gold
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	if (Loot)
	{
		UWorld* CurrentWorld = GetWorld();
		if (CurrentWorld)
		{

			CurrentWorld->SpawnActor<ADroppedItemBase>(Loot, GetActorLocation(), GetActorRotation(), SpawnInfo);
		}
	}
	/*UE_LOG(LogClass, Warning, TEXT("%s"), Gold);*/
}

void AEnemyBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AEnemyBase, CurrentHP);
	DOREPLIFETIME(AEnemyBase, Loot);
}

