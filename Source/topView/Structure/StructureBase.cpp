// Fill out your copyright notice in the Description page of Project Settings.

#include "StructureBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Character/Operator.h"

// Sets default values
AStructureBase::AStructureBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));

	Body->SetupAttachment(Sphere);
}

// Called when the game starts or when spawned
void AStructureBase::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AStructureBase::OnBeginOverlap);

	Sphere->OnComponentEndOverlap.AddDynamic(this, &AStructureBase::OnEndOverlap);
}

// Called every frame
void AStructureBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStructureBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		auto Char = Cast<AOperator>(OtherActor);
		if (Char)
		{
			Char->AddInteractableList(this);
		}
	}
}


void AStructureBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		auto Char = Cast<AOperator>(OtherActor);
		if (Char)
		{
			Char->RemoveInteractableList(this);
		}
	}

}

void AStructureBase::DoSomething(AActor* PlayerController)
{
}
