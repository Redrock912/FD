// Fill out your copyright notice in the Description page of Project Settings.

#include "Operator.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BulletDamageType.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AOperator::AOperator()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	
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

}

// Called to bind functionality to input
void AOperator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AOperator::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AOperator::MoveRight);
	
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed, this, &AOperator::OnShot);
}
void AOperator::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AOperator::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}


void AOperator::OnShot()
{
	FVector TraceStart;
	FVector TraceEnd;

	TraceStart = GetActorLocation();
	TraceEnd = GetActorLocation() + GetActorForwardVector() * AttackRange;
	
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
		
		

	}


	
	//UGameplayStatics::ApplyDamage(OutHit.GetActor(),50.0f,)
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

