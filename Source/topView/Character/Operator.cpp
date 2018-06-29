// Fill out your copyright notice in the Description page of Project Settings.

#include "Operator.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BulletDamageType.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Item/ItemBase.h"
#include "Item/ItemDataTableComponent.h"
#include "Character/PC_Operator.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

// Sets default values
AOperator::AOperator()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Player"));
	
}

// Called when the game starts or when spawned
void AOperator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOperator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetDirection();

}

void AOperator::SetDirection()
{
	APC_Operator* PlayerController = Cast<APC_Operator>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	

	FHitResult OutHit;
	if (PlayerController)
	{
		bool Result = PlayerController->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_EngineTraceChannel1), true, OutHit);
	
		if (Result)
		{
			// Rotation of character to clicked point 
			FRotator PlayerRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), OutHit.Location);


			FRotator FinalRotator = FRotator( GetActorRotation().Pitch, PlayerRotation.Yaw, GetActorRotation().Roll);

			GetCapsuleComponent()->SetWorldRotation(FinalRotator);
		}

	}
	
}

// Called to bind functionality to input
void AOperator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AOperator::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AOperator::MoveRight);
	
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed, this, &AOperator::StartFire);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &AOperator::StopFire);
}
void AOperator::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		//AddMovementInput(GetActorRightVector(), Value);
		AddMovementInput(FVector(0, 1, 0), Value);
	}
}

void AOperator::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		//AddMovementInput(GetActorForwardVector(), Value);
		AddMovementInput(FVector(1, 0, 0), Value);
	}
}


void AOperator::OnShot()
{
	UE_LOG(LogClass, Warning, TEXT("FireInput"));

	if (bIsShooting == false)
	{
		return;
	}

	FVector TraceStart;
	FVector TraceEnd;

	TraceStart = GetActorLocation();
	TraceEnd = GetActorLocation() + GetActorForwardVector() * AttackRange;
	
	UE_LOG(LogClass, Warning, TEXT("TraceStart: %f %f %f"),GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	UE_LOG(LogClass, Warning, TEXT("TraceEnd: %f %f %f"), TraceEnd.X, TraceEnd.Y, TraceEnd.Z);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	TArray<AActor*> IgnoreObjects;
	FHitResult OutHit;
	ObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	ObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	IgnoreObjects.Add(this); // 본인 제외


	bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), TraceStart, TraceEnd, ObjectType,
		false,
		IgnoreObjects,
		EDrawDebugTrace::ForDuration,
		OutHit,
		true);

	if (Result)
	{
		DeathImpactVector = OutHit.ImpactPoint - TraceStart;
		UGameplayStatics::ApplyPointDamage(OutHit.GetActor(), 50.0f,
			TraceEnd - TraceStart, OutHit, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, UBulletDamageType::StaticClass());
		
		
		UE_LOG(LogClass, Warning, TEXT("Hit"));
	}

	if (bIsShooting)
	{
		GetWorldTimerManager().SetTimer(ShootTimerHandle,this,&AOperator::OnShot,RecoilTime);
	}

	
	//UGameplayStatics::ApplyDamage(OutHit.GetActor(),50.0f,)
}

void AOperator::StartFire()
{
	bIsShooting = true;
	OnShot();
}


void AOperator::StopFire() 
{
	bIsShooting = false;
}

float AOperator::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	AOperator* Player = Cast<AOperator>(DamageCauser);

	DeathImpactVector = Player->DeathImpactVector;
	DeathImpactVector.Normalize();
	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		CurrentHP -= DamageAmount;
	}

	if (CurrentHP <= 0)
	{
	

		OnDead(DeathImpactVector);
	}
	UE_LOG(LogClass, Warning, TEXT("%f %f %f"), DeathImpactVector.X, DeathImpactVector.Y, DeathImpactVector.Z);
	return 0.0f;
}

void AOperator::OnDead(FVector Impact)
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->AddForce(2000000*Impact);
	
	SetLifeSpan(3.0f);

	
}

void AOperator::ConsumeItem(AItemBase * Item)
{
	float Recover =	Item->ItemDataTable->GetItemData(Item->ItemIndex).Power;

	auto PlayerController = Cast<APC_Operator>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (IsLocallyControlled())
	{
		if (Item && !Item->IsPendingKill())
		{
			if (CurrentHP < MaxHP)
			{
				CurrentHP = FMath::Clamp((CurrentHP + Recover), 0.0f, 100.0f);
				PlayerController->C2S_DestroyItem(Item);
			}
		}
	}

}

void AOperator::EquipItem(AItemBase * Item)
{

}

