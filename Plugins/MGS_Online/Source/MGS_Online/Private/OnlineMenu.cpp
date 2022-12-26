// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlineMenu.h"
#include "MGS_OnlineSubsystem.h"

#include "Components/Button.h"

void UOnlineMenu::LoadMenu()
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	if (UWorld* World = GetWorld())
	{
		if (APlayerController* PlayerController = World->GetFirstPlayerController())
		{
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputMode);
			PlayerController->SetShowMouseCursor(true);
		}

		if (UGameInstance* GameInstance = GetGameInstance())
		{
			MGS_OnlineSubsystem = GameInstance->GetSubsystem<UMGS_OnlineSubsystem>();
		}
	}
	if (MGS_OnlineSubsystem)
	{
		MGS_OnlineSubsystem->MGSCreateSessionCompleted.AddDynamic(this, &ThisClass::OnCreateSession);
	}
}

void UOnlineMenu::UnloadMenu()
{
	if (UWorld* World = GetWorld())
	{
		if (APlayerController* PlayerController = World->GetFirstPlayerController())
		{
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->SetShowMouseCursor(false);
		}
	}
	RemoveFromParent();
}

void UOnlineMenu::HostButtonClicked()
{
	if (MGS_OnlineSubsystem)
	{
		MGS_OnlineSubsystem->CreateGameSession(MaxPlayers, GameType, LevelPath);
	}
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Yellow,
			FString(TEXT("Host button clicked"))
		);
	}
}

void UOnlineMenu::JoingButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Yellow,
			FString(TEXT("Join button clicked"))
		);
	}
}

bool UOnlineMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &ThisClass::UOnlineMenu::HostButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoingButtonClicked);
	}

	return true;
}

void UOnlineMenu::NativeDestruct()
{
	UnloadMenu();
	Super::NativeDestruct();
}

void UOnlineMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Green,
				FString(TEXT("Game Session created!"))
			);
		}
		if (UWorld* World = GetWorld())
		{
			LevelPath = LevelPath + FString(TEXT("?listen"));
			World->ServerTravel(LevelPath);
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("Session was not created!"))
			);
		}
	}
}
