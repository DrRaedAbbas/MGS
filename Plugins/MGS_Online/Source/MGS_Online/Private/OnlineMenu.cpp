// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlineMenu.h"
#include "MGSFunctionLibrary.h"
#include "MGS_OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"


void UOnlineMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
	//Define widget button type
	HostText->SetText(FText::FromString(HostButtonLabel));
	FindText->SetText(FText::FromString(FindButtonLabel));
	JoinText->SetText(FText::FromString(JoinButtonLabel));

	switch (ButtonType)
	{
		case EButtonType::NONE:
		{
			HostButton->SetVisibility(ESlateVisibility::Visible);
			JoinButton->SetVisibility(ESlateVisibility::Visible);
			FindButton->SetVisibility(ESlateVisibility::Visible);
			HostText->SetVisibility(ESlateVisibility::Visible);
			FindText->SetVisibility(ESlateVisibility::Visible);
			JoinText->SetVisibility(ESlateVisibility::Visible);
			break;
		}
		case EButtonType::HostButton:
		{
			HostButton->SetVisibility(ESlateVisibility::Visible);
			JoinButton->SetVisibility(ESlateVisibility::Collapsed);
			FindButton->SetVisibility(ESlateVisibility::Collapsed);
			HostText->SetVisibility(ESlateVisibility::Visible);
			JoinText->SetVisibility(ESlateVisibility::Collapsed);
			FindText->SetVisibility(ESlateVisibility::Collapsed);
			break;
		}
		case EButtonType::FindButton:
		{
			HostButton->SetVisibility(ESlateVisibility::Collapsed);
			JoinButton->SetVisibility(ESlateVisibility::Collapsed);
			FindButton->SetVisibility(ESlateVisibility::Visible);
			HostText->SetVisibility(ESlateVisibility::Collapsed);
			JoinText->SetVisibility(ESlateVisibility::Collapsed);
			FindText->SetVisibility(ESlateVisibility::Visible);
			break;
		}
		case EButtonType::JoinButton:
		{
			HostButton->SetVisibility(ESlateVisibility::Collapsed);
			JoinButton->SetVisibility(ESlateVisibility::Visible);
			FindButton->SetVisibility(ESlateVisibility::Collapsed);
			HostText->SetVisibility(ESlateVisibility::Collapsed);
			JoinText->SetVisibility(ESlateVisibility::Visible);
			FindText->SetVisibility(ESlateVisibility::Collapsed);
			break;
		}
		default:
		{
			HostButton->SetVisibility(ESlateVisibility::Visible);
			JoinButton->SetVisibility(ESlateVisibility::Visible);
			FindButton->SetVisibility(ESlateVisibility::Visible);
			HostText->SetVisibility(ESlateVisibility::Visible);
			FindText->SetVisibility(ESlateVisibility::Visible);
			JoinText->SetVisibility(ESlateVisibility::Visible);
			break;
		}
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
		HostButton->OnClicked.AddDynamic(this, &ThisClass::JoingButtonClicked);
	}
	if(FindButton)
	{
		FindButton->OnClicked.AddDynamic(this, &ThisClass::FindButtonClicked);
	}

	return true;
}

void UOnlineMenu::NativeDestruct()
{
	UnloadMenu();
	Super::NativeDestruct();
}

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
		MGS_OnlineSubsystem->MGSFindSessionsCompleted.AddUObject(this, &ThisClass::OnFindSessions);
		MGS_OnlineSubsystem->MGSJoinSessionCompleted.AddUObject(this, &ThisClass::OnJoinSession);
		MGS_OnlineSubsystem->MGSStartSessionCompleted.AddDynamic(this, &ThisClass::OnStartSession);
		MGS_OnlineSubsystem->MGSDestroySessionCompleted.AddDynamic(this, &ThisClass::OnDestroySession);
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
	MGSFunctionLibrary->DisplayDebugMessage(FString(TEXT("Host button clicked")), FColor::Cyan);
	if (MGS_OnlineSubsystem)
	{
		MGS_OnlineSubsystem->CreateGameSession(MaxPlayers, GameType);
	}
}

void UOnlineMenu::JoingButtonClicked()
{
	MGSFunctionLibrary->DisplayDebugMessage(FString(TEXT("Join button clicked")), FColor::Cyan);
	
	if (!SessionSearchResult.IsValid()) return;
	if(MGS_OnlineSubsystem) 
	{
		MGS_OnlineSubsystem->JoinGameSession(SessionSearchResult);
	}
}

void UOnlineMenu::FindButtonClicked()
{
	MGSFunctionLibrary->DisplayDebugMessage(FString(TEXT("Find button clicked")), FColor::Cyan);
	if (MGS_OnlineSubsystem)
	{
		MGS_OnlineSubsystem->FindGameSessions();
	}
}

void UOnlineMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		MGSFunctionLibrary->DisplayDebugMessage(FString(TEXT("Game Session created!")), FColor::Green);
		
		if (UWorld* World = GetWorld())
		{
			LevelPath = LevelPath + FString(TEXT("?listen"));
			World->ServerTravel(LevelPath);
		}
	}
	else
	{
		MGSFunctionLibrary->DisplayDebugMessage(FString(TEXT("Session was not created!")), FColor::Red);
	}
}

void UOnlineMenu::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful)
{
	if (MGS_OnlineSubsystem == nullptr) return;

	MGSFunctionLibrary->DisplayDebugMessage(FString(TEXT("Finding Game Sessions!")), FColor::Cyan);
	for (auto Result : SessionResults)
	{
		if(Result.Session.NumOpenPublicConnections < 1) continue;

		FString FoundGameType;
		Result.Session.SessionSettings.Get(FName("MatchType"), FoundGameType);
		if (FoundGameType == GameType)
		{
			SessionSearchResult = Result;
			MGSFunctionLibrary->DisplayDebugMessage(FString(TEXT("Game Session Found")), FColor::Green);
			break;
		}
	}
}

void UOnlineMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	if(IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			FString Address;
			SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);
			APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
			if (PlayerController)
			{
				PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
			}
		}
		else
		{
			MGSFunctionLibrary->DisplayDebugMessage(FString(TEXT("CANNOT Joing Game!")), FColor::Red);
		}
	}
	else
	{
		MGSFunctionLibrary->DisplayDebugMessage(FString(TEXT("Subsystem Does Not Exist!")), FColor::Red);
	}
}

void UOnlineMenu::OnStartSession(bool bWasSuccessful)
{
}

void UOnlineMenu::OnDestroySession(bool bWasSuccessful)
{
}
