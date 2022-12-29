// Copy righted to RAED ABBAS 2023

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MGS_INVENTORY_API UItemPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MGS|Inventory")
	FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MGS|Inventory")
	USkeletalMesh* ItemSkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MGS|Inventory")
	UStaticMesh* ItemStaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MGS|Inventory")
	FName EquipSocketName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MGS|Inventory")
	UAnimSequence* ItemEqipingAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MGS|Inventory")
	UAnimSequence* ItemEqippedAnimation;
};
