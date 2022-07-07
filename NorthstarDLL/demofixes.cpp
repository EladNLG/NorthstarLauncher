#include "pch.h"
#include "convar.h"
#include "NSMem.h"

ON_DLL_LOAD_CLIENT("engine.dll", EngineDemoFixes, [](HMODULE baseAddress)
{
	// allow demo recording on loopback
	NSMem::NOP((uintptr_t)baseAddress + 0x8E1B1, 2);
	NSMem::NOP((uintptr_t)baseAddress + 0x56CC3, 2);
})

ON_DLL_LOAD_CLIENT_RELIESON("client.dll", ClientDemoFixes, ConVar, [](HMODULE baseAddress)
{
	// change default values of demo cvars to enable them by default, but not autorecord
	// this is before Host_Init, the setvalue calls here will get overwritten by custom cfgs/launch options
	ConVar* Cvar_demo_enableDemos = R2::g_pCVar->FindVar("demo_enabledemos");
	Cvar_demo_enableDemos->m_pszDefaultValue = "1";
	Cvar_demo_enableDemos->SetValue(true);

	ConVar* Cvar_demo_writeLocalFile = R2::g_pCVar->FindVar("demo_writeLocalFile");
	Cvar_demo_writeLocalFile->m_pszDefaultValue = "1";
	Cvar_demo_writeLocalFile->SetValue(true);

	ConVar* Cvar_demo_autoRecord = R2::g_pCVar->FindVar("demo_autoRecord");
	Cvar_demo_autoRecord->m_pszDefaultValue = "0";
	Cvar_demo_autoRecord->SetValue(false);
})