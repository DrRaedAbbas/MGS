// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "OnlineMenu.generated.h"

class UButton;
class UTextBlock;

UENUM(BlueprintType)
enum class EButtonType : uint8
{
	NONE,
	HostButton,
	JoinButton,
	FindButton	
};

UCLASS()
class MGS_ONLINE_API UOnlineMenu : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativePreConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void LoadMenu();
	UFUNCTION(BlueprintCallable)
	void UnloadMenu();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MGS Online Settings")
	int32 MaxPlayers = 4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MGS Online Settings")
	FString GameType = FString("FreeForAll");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MGS Online Settings")
	FString LevelPath = FString("/Game/Maps/Lobby");
	
private:
	class UMGS_OnlineSubsystem* MGS_OnlineSubsystem;
	class UMGSFunctionLibrary* MGSFunctionLibrary;

	//hosting
	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HostText;
	UFUNCTION()
	void HostButtonClicked();

	//Joining
	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* JoinText;
	UFUNCTION()
	void JoingButtonClicked();

	//Finding
	UPROPERTY(meta = (BindWidget))
	UButton* FindButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FindText;
	UFUNCTION()
	void FindButtonClicked();
	
	FOnlineSessionSearchResult SessionSearchResult;

protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;
	//Custom delegates callbacks
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);

	//Custom Buttons
	UPROPERTY(EditAnywhere)
	EButtonType ButtonType = EButtonType::NONE;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "ButtonType == EButtonType::HostButton || ButtonType == EButtonType::NONE", EditConditionHides), Category = "MGS Online Settings")
	FString HostButtonLabel = FString("Host");
	UPROPERTY(EditAnywhere, meta = (EditCondition = "ButtonType == EButtonType::FindButton || ButtonType == EButtonType::NONE", EditConditionHides), Category = "MGS Online Settings")
	FString FindButtonLabel = FString("Find");
	UPROPERTY(EditAnywhere, meta = (EditCondition = "ButtonType == EButtonType::JoinButton || ButtonType == EButtonType::NONE", EditConditionHides), Category = "MGS Online Settings")
	FString JoinButtonLabel = FString("Join");
};
