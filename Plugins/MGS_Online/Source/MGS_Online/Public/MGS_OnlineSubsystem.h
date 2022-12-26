// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MGS_OnlineSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MGS_ONLINE_API UMGS_OnlineSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMGS_OnlineSubsystem();

protected:

private:
	IOnlineSessionPtr SessionInterface;
};
