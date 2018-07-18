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
#include "Structure/StructureBase.h"
#include "UnrealNetwork.h"
#include "Public/TimerManager.h"


// Sets default values
AOperator::AOperator()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName(TEXT("Player")));
}



// Called when the game starts or when spawned
void AOperator::BeginPlay()
{
	Super::BeginPlay();
	
	// HP setup
	CurrentHP = MaxHP;
	
	auto PC = Cast<APC_Operator>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UE_LOG(LogClass, Warning, TEXT("%s"), PC)

	/*GetWorldTimerManager().SetTimer(TimerHandle, this, &AOperator::SetDirection,0.05f,true);*/
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
		{
			bool Result = PlayerController->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_EngineTraceChannel1), true, OutHit);

			if (Result)
			{
				//UE_LOG(LogClass, Warning, TEXT("%s"), PlayerController);
				// Rotation of character to clicked point 
				FRotator PlayerRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), OutHit.Location);



				
				LookingRotation = FRotator(GetActorRotation().Pitch, PlayerRotation.Yaw, GetActorRotation().Roll);



				// 계산은 권한이 있는 쪽에서 한다. 클라이언트는 다시 그걸 받아서 적용.
				if (HasAuthority())
				{

					S2C_SetDirection(LookingRotation);
				}
				else
				{
					if (IsLocallyControlled())
					{
						// 클라이언트 상에서 돌려주고, 값을 나중에 서버에 보낸다.
						GetCapsuleComponent()->SetWorldRotation(LookingRotation);
						C2S_SetDirection(LookingRotation);
					}
				}
			}

		}

	}



	
	
	
	
}

bool AOperator::C2S_SetDirection_Validate(FRotator Rotation)
{
	return true;
}

void AOperator::C2S_SetDirection_Implementation(FRotator NewRotation)
{
	GetCapsuleComponent()->SetWorldRotation(NewRotation);
}

void AOperator::S2C_SetDirection_Implementation(FRotator Rotation)
{
	GetCapsuleComponent()->SetWorldRotation(Rotation);
}

// Called to bind functionality to input
void AOperator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AOperator::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AOperator::MoveRight);
	
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed, this, &AOperator::StartFire);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &AOperator::StopFire);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AOperator::Interact);
}

void AOperator::Interact()
{
	// 각 Structure 마다 따로 일 지정
	if (InteractableList.Num()!=0)
	{
		InteractableList.Top()->DoSomething(this);
	}
	
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

void AOperator::StartFire()
{
	bIsShooting = true;
	OnShot();
}


void AOperator::StopFire()
{
	bIsShooting = false;
}



void AOperator::OnShot()
{

	if (bIsShooting == false)
	{
		return;
	}

	
	C2S_OnShot();

	if (bIsShooting)
	{
		GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &AOperator::OnShot, RecoilTime);
	}
}


bool AOperator::C2S_OnShot_Validate()
{
	return true;
}

void AOperator::C2S_OnShot_Implementation()
{
	//UE_LOG(LogClass, Warning, TEXT("FireInput"));

	/*if (bIsShooting == false)
	{
		return;
	}

	FVector TraceStart;
	FVector TraceEnd;

	TraceStart = GetActorLocation();
	TraceEnd = GetActorLocation() + GetActorForwardVector() * AttackRange;*/
	
	//UE_LOG(LogClass, Warning, TEXT("TraceStart: %f %f %f"),GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	//UE_LOG(LogClass, Warning, TEXT("TraceEnd: %f %f %f"), TraceEnd.X, TraceEnd.Y, TraceEnd.Z);
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
		
		
		UE_LOG(LogClass, Warning, TEXT("Hit"));
	}

	//if (bIsShooting)
	//{
	//	GetWorldTimerManager().SetTimer(ShootTimerHandle,this,&AOperator::OnShot,RecoilTime);
	//}

	
	//UGameplayStatics::ApplyDamage(OutHit.GetActor(),50.0f,)
}


float AOperator::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (!HasAuthority())
	{
		return 0;
	}

	AOperator* Player = Cast<AOperator>(DamageCauser);

	DeathImpactVector = Player->DeathImpactVector;
	DeathImpactVector.Normalize();
	CurrentHP -= DamageAmount;
	

	if (CurrentHP <= 0)
	{
		//GetWorldTimerManager().ClearTimer(TimerHandle);
		OnDead(DeathImpactVector);
	}

	//UE_LOG(LogClass, Warning, TEXT("%f %f %f"), DeathImpactVector.X, DeathImpactVector.Y, DeathImpactVector.Z);
	return 0.0f;
}


// 죽는 처리
void AOperator::OnDead_Implementation(FVector Impact)
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->AddForce(2000000 * Impact);

	SetLifeSpan(3.0f);
}

void AOperator::AddInteractableList(AStructureBase * Structure)
{
	if (IsLocallyControlled())
	{
		if (Structure && !Structure->IsPendingKill())
		{
			InteractableList.Add(Structure);
		}
	}

}

void AOperator::RemoveInteractableList(AStructureBase * Structure)
{
	if (IsLocallyControlled())
	{
		if (Structure && !Structure->IsPendingKill())
		{
			InteractableList.Remove(Structure);
		}
	}
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

void AOperator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOperator, bIsShooting);
	DOREPLIFETIME(AOperator, CurrentHP);
	DOREPLIFETIME(AOperator, LookingRotation);
	DOREPLIFETIME(AOperator, DeathImpactVector);
}

