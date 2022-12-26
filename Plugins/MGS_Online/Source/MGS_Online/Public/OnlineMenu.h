// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "OnlineMenu.generated.h"

class UButton;

UCLASS()
class MGS_ONLINE_API UOnlineMenu : public UUserWidget
{
	GENERATED_BODY()
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

	//hosting
	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;
	UFUNCTION()
	void HostButtonClicked();

	//Joining
	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;
	UFUNCTION()
	void JoingButtonClicked();

protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;
	//Custom delegates callbacks
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
};
