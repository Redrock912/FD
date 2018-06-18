// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBase.h"
#include "UnrealNetwork.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ItemDataTableComponent.h"
#include "Character/Operator.h"
#include "Engine/StreamableManager.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));

	Sphere->SetupAttachment(GetStaticMeshComponent());

	Sphere->SetSphereRadius(100.0f);
	Sphere->bGenerateOverlapEvents = true;

	ItemDataTable = CreateDefaultSubobject<UItemDataTableComponent>(TEXT("ItemDataTable"));

	bReplicates = true;
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (ItemDataTable && ItemDataTable->DataTable)
	{
		FItemDataTable DataTable = ItemDataTable->GetItemData(ItemIndex);

		FStreamableManager AssetLoader;
		GetStaticMeshComponent()->SetStaticMesh(AssetLoader.LoadSynchronous<UStaticMesh>(DataTable.ItemMesh));

		Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnBeginOverlap);
	}

}

void AItemBase::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	EEquipSlot ItemType = ItemDataTable->GetItemData(ItemIndex).ItemEquipSlot;

	switch (ItemType)
	{
	case EEquipSlot::NotUse:
	{
		break;
	}
	case EEquipSlot::Weapon:
	{
		break;
	}
	default:
		break;
	}
}

void AItemBase::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

void AItemBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AItemBase, ItemIndex);
}



