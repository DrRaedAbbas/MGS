// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MGS_OnlineSubsystem.generated.h"

/**
 * Custom delegates
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMGSCreateSessionCompleted, bool, bWasSuccessful);

UCLASS()
class MGS_ONLINE_API UMGS_OnlineSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMGS_OnlineSubsystem();

	//Functions for menus
	void CreateGameSession(int32 MaxPlayers, FString MatchType, FString PathToLevel);
	void FindGameSessions(int32 MaxSearchResults);
	void JoinGameSession(const FOnlineSessionSearchResult& SessionSearchResult);
	void StartGameSession();
	void DestroyGameSession();

	FMGSCreateSessionCompleted MGSCreateSessionCompleted;

protected:
	//callbacks for subsystem's delegates
	void OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsCompleted(bool bWasSuccessful);
	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnStartSessionCompleted(FName SessionName, bool bWasSuccessful);
	void OnDestroySessionCompleted(FName SessionName, bool bWasSuccessful);

private:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSettings> SessionSettings;
	FString LevelToTravelTo;

	//To bind subsystem callbacks
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionHandle;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsHandle;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionHandle;
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionHandle;
	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionHandle;
};
