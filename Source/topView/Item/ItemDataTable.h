// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataTable.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Unknown = 0				UMETA(Display = "Unknown"),
	Consume = 1				UMETA(Display = "Consume"),
	Equip = 2				UMETA(Display = "Equip")
};

UENUM(BlueprintType)
enum class EEquipSlot : uint8
{
	NotUse = 0						UMETA(Display = "NotUse"),
	Weapon = 1						UMETA(Display = "Weapon")
};

/**
*
*/
USTRUCT(BlueprintType)
struct TOPVIEW_API FItemDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	//ItemIndex	ItemName	ItemType	ItemEquipSlot	ItemFloat01	ItemCount	ItemThumnail	ItemMesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int ItemIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		EEquipSlot ItemEquipSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float AttackRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float DamagePerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int ItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TAssetPtr<class UTexture2D> ItemThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TAssetPtr<class UStaticMesh> ItemMesh;
};
