// Fill out your copyright notice in the Description page of Project Settings.


#include "MGS_OnlineSubsystem.h"
#include "OnlineSubsystem.h"

UMGS_OnlineSubsystem::UMGS_OnlineSubsystem()
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if(Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
	}
}
