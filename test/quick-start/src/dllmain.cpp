#include "hijack.h"
#include <AlphaRomCrack/Bypass.h>
#include <AlphaRomCrack/DllExtract.h>


static auto __stdcall NatsuNoOwarinoNirvanaCrack(AlphaRomCrack::LPSarcheckInfo lpInfo) -> void
{
	// 夏の終わりのニルヴァーナ
	*(DWORD*)(((PBYTE)lpInfo->pDllData) + 0x2BA000) = 0x90000CC2; // Path DllEntryPoint
	*(DWORD*)(((PBYTE)lpInfo->pDllData) + 0x002064) = 0x909090C3; // Path SARCHECK (export function)
}

static auto StartHook() -> void
{
	AlphaRomCrack::Bypass(NatsuNoOwarinoNirvanaCrack);
	//AlphaRomCrack::ExtractSarcheck();
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