#include <version/hijack.h>
#include <detours.h>


using Fn_VirtualAlloc_t = decltype(&::VirtualAlloc);
static Fn_VirtualAlloc_t sg_fnVirtualAlloc;

static LPVOID WINAPI VirtualAlloc_Hook(LPVOID lpAddress, SIZE_T dwSize, DWORD  flAllocationType, DWORD  flProtec)
{
	if (dwSize == 0x00572000) //alloc size of sarcheck.dll
	{
		if (*(DWORD*)0x00AFB25D == 0x5004EC83) // check entrypoint
		{
			*(DWORD*)0x00AFB25D = 0x90000CC2; // entrypoint => ret 0xC
			DetourTransactionBegin();
			DetourDetach(&(PVOID&)sg_fnVirtualAlloc, VirtualAlloc_Hook);
			DetourTransactionCommit();
		}
	}

	return sg_fnVirtualAlloc(lpAddress, dwSize, flAllocationType, flProtec);
}

static void StartHook()
{
	sg_fnVirtualAlloc = ::VirtualAlloc;

	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)sg_fnVirtualAlloc, VirtualAlloc_Hook);
	DetourTransactionCommit();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
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