// Fill out your copyright notice in the Description page of Project Settings.


#include "MGSFunctionLibrary.h"
#include "Math/Color.h"

FString UMGSFunctionLibrary::DisplayDebugMessage(FString DebugMessage, FLinearColor MessageColor)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			MessageColor.ToFColor(true),
			DebugMessage
		);
	}
	return DebugMessage;
}
