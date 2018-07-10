// Fill out your copyright notice in the Description page of Project Settings.

#include "DroppedItemBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Character/OperatorPS.h"
#include "Character/Operator.h"

// Sets default values
ADroppedItemBase::ADroppedItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// body 
	ItemBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item"));

	RootComponent = ItemBody;

	ItemBody->SetMobility(EComponentMobility::Movable);
	ItemBody->SetSimulatePhysics(true);

	// collision
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(ItemBody);

	Sphere->SetSphereRadius(200.0f);
}

// Called when the game starts or when spawned
void ADroppedItemBase::BeginPlay()
{
	Super::BeginPlay();

	FVector ImpactVector = FMath::VRand();

	float ImpactScale = FMath::FRandRange(ImpactMin, ImpactMax);

	ItemBody->AddForce(ImpactVector * ImpactScale);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ADroppedItemBase::OnBeginOverlap);
	
}

// Called every frame
void ADroppedItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADroppedItemBase::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	

}



