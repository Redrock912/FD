// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemDataTableComponent.h"
#include "ConstructorHelpers.h"

// Sets default values for this component's properties
UItemDataTableComponent::UItemDataTableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	static ConstructorHelpers::FObjectFinder<UDataTable>Item_DT(TEXT(""));

	if (Item_DT.Succeeded())
	{
		DataTable = Item_DT.Object;
	}
}


// Called when the game starts
void UItemDataTableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UItemDataTableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FItemDataTable & UItemDataTableComponent::GetItemData(int ItemIndex)
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return *DataTable->FindRow<FItemDataTable>(*FString::FromInt(ItemIndex), TEXT("ItemIndex"));

}

