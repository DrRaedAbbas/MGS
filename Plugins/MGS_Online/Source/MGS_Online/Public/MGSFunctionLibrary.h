// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MGSFunctionLibrary.generated.h"

UCLASS()
class MGS_ONLINE_API UMGSFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MGS|Functions Library")
	static FString DisplayDebugMessage(FString DebugMessage, FLinearColor MessageColor);
};
