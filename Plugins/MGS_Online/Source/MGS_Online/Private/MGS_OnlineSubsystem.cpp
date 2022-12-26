// Fill out your copyright notice in the Description page of Project Settings.


#include "MGS_OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

UMGS_OnlineSubsystem::UMGS_OnlineSubsystem():
CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionCompleted)),
FindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionsCompleted)),
JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionCompleted)),
StartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionCompleted)),
DestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionCompleted))
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if(Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
	}
}

void UMGS_OnlineSubsystem::CreateGameSession(int32 MaxPlayers, FString MatchType, FString PathToLevel)
{
	if (!SessionInterface) return;

	if (auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession))
		SessionInterface->DestroySession(NAME_GameSession);

	CreateSessionHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);
	SessionSettings = MakeShareable(new FOnlineSessionSettings());
	SessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
	SessionSettings->NumPublicConnections = MaxPlayers;
	SessionSettings->bAllowJoinInProgress = true;
	SessionSettings->bAllowJoinViaPresence = true;
	SessionSettings->bShouldAdvertise = true;
	SessionSettings->bUsesPresence = true;
	SessionSettings->Set(FName("MatchType"), MatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	LevelToTravelTo = PathToLevel;

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	const FUniqueNetId& LocalPlayerID = *LocalPlayer->GetPreferredUniqueNetId();

	if (!SessionInterface->CreateSession(LocalPlayerID, NAME_GameSession, *SessionSettings))
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionHandle);
		MGSCreateSessionCompleted.Broadcast(false);
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Blue,
			FString(TEXT("Creating Game Session"))
		);
	}
}
void UMGS_OnlineSubsystem::OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful)
{
	/*if (UWorld* World = GetWorld())
	{
		LevelToTravelTo = LevelToTravelTo + FString(TEXT("?listen"));
		World->ServerTravel(LevelToTravelTo);
	}*/
	
	MGSCreateSessionCompleted.Broadcast(bWasSuccessful);
	if (SessionInterface) SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionHandle);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Green,
			FString(TEXT("Create Session Completed"))
		);
	}

}

void UMGS_OnlineSubsystem::FindGameSessions(int32 MaxSearchResults)
{
}
void UMGS_OnlineSubsystem::OnFindSessionsCompleted(bool bWasSuccessful)
{
}

void UMGS_OnlineSubsystem::JoinGameSession(const FOnlineSessionSearchResult& SessionSearchResult)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Blue,
			FString(TEXT("Joining Game Session"))
		);
	}
}
void UMGS_OnlineSubsystem::OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Green,
			FString(TEXT("Join Session Completed"))
		);
	}
}

void UMGS_OnlineSubsystem::StartGameSession()
{
}
void UMGS_OnlineSubsystem::OnStartSessionCompleted(FName SessionName, bool bWasSuccessful)
{
}

void UMGS_OnlineSubsystem::DestroyGameSession()
{
}
void UMGS_OnlineSubsystem::OnDestroySessionCompleted(FName SessionName, bool bWasSuccessful)
{
}
