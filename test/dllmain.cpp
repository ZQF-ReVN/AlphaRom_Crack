#include "hijack.h"
#include <AlphaRomCrack/Bypass.h>
#include <AlphaRomCrack/DllExtract.h>


static auto StartHook() -> void
{
	AlphaRomCheck::Bypass();
}

auto APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) -> BOOL
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		StartHook();
		CreateHijack();
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		FreeHijack();
		break;
	}
	return TRUE;
}