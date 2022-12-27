// Copy righted to RAED ABBAS 2022


#include "MGSFunctionLibrary.h"
#include "Math/Color.h"

FString UMGSFunctionLibrary::DisplayDebugMessage(FString DebugMessage, FLinearColor MessageColor)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.f,
			MessageColor.ToFColor(true),
			DebugMessage
		);
	}
	return DebugMessage;
}
