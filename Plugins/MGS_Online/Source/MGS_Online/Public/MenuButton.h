// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"

#include "MenuButton.generated.h"

UENUM(BlueprintType)
enum class EButtonType : uint8
{
	NONE,
	HostButton,
	JoinButton,
	FindButton
};

UCLASS()
class MGS_ONLINE_API UMenuButton : public UButton
{
	GENERATED_BODY()

	UMenuButton();

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

public:
	class UOnlineMenu* MainMenu;

protected:
	UPROPERTY(EditAnywhere)
	EButtonType ButtonType = EButtonType::NONE;

	UFUNCTION()
	void OnButtonClicked();
};