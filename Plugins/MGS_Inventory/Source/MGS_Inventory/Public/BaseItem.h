// Copy righted to RAED ABBAS 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventorySubsystem.h"

#include "BaseItem.generated.h"

UCLASS()
class MGS_INVENTORY_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseItem();
	virtual void Tick(float DeltaTime) override;
	void ShowItemWidget(bool bShowWidget);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "MGS|Item Details")
	USceneComponent* RootScene;
	UPROPERTY(VisibleAnywhere, Category = "MGS|Item Details")
	class USphereComponent* SphereCollision;
	UPROPERTY(VisibleAnywhere, Category = "MGS|Item Details")
	USkeletalMeshComponent* ItemMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MGS|Item Details")
	class UWidgetComponent* ItemWidget;

private:
	class UInventorySubsystem* InventorySubsystem;

	UPROPERTY(EditAnywhere, Category = "MGS|Item Details")
	EItemState ItemState = EItemState::E_Initial;

	UFUNCTION(BlueprintCallable, Category = "MGS|Item Details")
	void UpdateOverlappingCharacter(ACharacter* OverlappingCharacter, bool bIsOverlapping);
};
