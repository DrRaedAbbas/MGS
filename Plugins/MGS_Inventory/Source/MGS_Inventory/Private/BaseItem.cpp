// Copy righted to RAED ABBAS 2023


#include "BaseItem.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Character/BaseCharacter.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootScene);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereCollision->SetSphereRadius(100);

	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Item"));
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	ItemMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	ItemWidget = CreateDefaultSubobject<UWidgetComponent>("Widget");
	ItemWidget->SetupAttachment(RootComponent);
	ItemWidget->SetVisibility(false);
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		if(UGameInstance* GameInstance = GetGameInstance())
		{
			InventorySubsystem = GameInstance->GetSubsystem<UInventorySubsystem>();
			InventorySubsystem->AddNewItem(this);
		}
		SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	}
}

void ABaseItem::UpdateOverlappingCharacter(ACharacter* OverlappingCharacter, bool bIsOverlapping)
{
	if (ABaseCharacter* NewCharacter = Cast<ABaseCharacter>(OverlappingCharacter))
	{
		if (!bIsOverlapping)
		{
			NewCharacter->SetOverlappedItem(nullptr);
			return;
		}
		NewCharacter->SetOverlappedItem(this);
	}
}

void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseItem::ShowItemWidget(bool bShowWidget)
{
	if (ItemWidget)
	{
		ItemWidget->SetVisibility(bShowWidget);
	}
}
