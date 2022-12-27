// Copy righted to RAED ABBAS 2023

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BaseGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MGS_API ALobbyGameMode : public ABaseGameMode
{
	GENERATED_BODY()

	ALobbyGameMode();

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

protected:
	class UMGSFunctionLibrary* MGSFunctionLibrary;

	UPROPERTY(EditAnywhere, Category = "MGS")
	FString LevelPath = FString("/Game/MGS/Maps/Lobby");

};
