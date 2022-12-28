// Copyright Epic Games, Inc. All Rights Reserved.

#include "MGS_Inventory.h"

#define LOCTEXT_NAMESPACE "FMGS_InventoryModule"

void FMGS_InventoryModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FMGS_InventoryModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMGS_InventoryModule, MGS_Inventory)