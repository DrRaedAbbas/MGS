// Copy righted to RAED ABBAS 2022

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

void UMenuButton::SetupButton(UOnlineMenu* NewMainMenu)
{
	if (NewMainMenu == nullptr) return;
	MainMenu = NewMainMenu;
	if (MainMenu)
	{
		MainMenu->OnButtonReady.AddDynamic(this, &ThisClass::OnButtonReady);
	}
}

#endif
#undef LOCTEXT_NAMESPACE

void UMenuButton::OnButtonClicked()
{
	if (MainMenu == nullptr) return;

	SetIsEnabled(false);

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

void UMenuButton::OnButtonReady(bool bButtonReady)
{
	SetIsEnabled(true);
}
