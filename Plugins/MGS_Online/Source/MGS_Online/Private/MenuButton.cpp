// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuButton.h"
#include "OnlineMenu.h"

#define LOCTEXT_NAMESPACE "UMG"

UMenuButton::UMenuButton()
{
	static ConstructorHelpers::FObjectFinder<USlateWidgetStyleAsset> CustomButtonStyle(TEXT("/Game/UI/Buttons/WS_Button"));
	SButton::FArguments ButtonDefaults;
	ButtonDefaults.ButtonStyle(CustomButtonStyle.Object);
	WidgetStyle = *ButtonDefaults._ButtonStyle;

	OnClicked.AddDynamic(this, &ThisClass::OnButtonClicked);
}
#if WITH_EDITOR
const FText UMenuButton::GetPaletteCategory()
{
	return LOCTEXT("", "MGS");
}

#endif
#undef LOCTEXT_NAMESPACE

void UMenuButton::OnButtonClicked()
{
	if (MainMenu == nullptr) return;

	switch (ButtonType)
	{
		case EButtonType::NONE:
		{
			break;
		}
		case EButtonType::HostButton:
		{
			MainMenu->HostButtonClicked();
			break;
		}
		case EButtonType::FindButton:
		{
			MainMenu->FindButtonClicked();
			break;
		}
		case EButtonType::JoinButton:
		{
			MainMenu->JoingButtonClicked();
			break;
		}
		default:
		{
			break;
		}
	}
}