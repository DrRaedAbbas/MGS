// Copy righted to RAED ABBAS 2023

#include "MGS_Combat.h"

#define LOCTEXT_NAMESPACE "FMGS_CombatModule"

void FMGS_CombatModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FMGS_CombatModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMGS_CombatModule, MGS_Combat)