#include <AlphaRomCrack/Bypass.h>
#include <AlphaRomCrack/SarcheckFinder.h>
#include <detours.h>


namespace AlphaRomCrack::Example
{
	using Fn_VirtualAlloc_t = decltype(&::VirtualAlloc);
	static Fn_VirtualAlloc_t sg_fnVirtualAlloc = ::VirtualAlloc;

	static LPVOID WINAPI VirtualAlloc_Hook(LPVOID lpAddress, SIZE_T dwSize, DWORD  flAllocationType, DWORD  flProtec)
	{
		if (dwSize == 0x00572000) //alloc size of sarcheck.dll
		{
			if (*(DWORD*)0x00AFB25D == 0x5004EC83) // check entrypoint
			{
				*(DWORD*)0x00AFB25D = 0x90000CC2; // entrypoint => ret 0xC
				// do not detach due to themida's iat encryption.
			}
		}

		return sg_fnVirtualAlloc(lpAddress, dwSize, flAllocationType, flProtec);
	}

	auto Bypass() -> void
	{
		::DetourRestoreAfterWith();
		::DetourTransactionBegin();
		::DetourUpdateThread(GetCurrentThread());
		::DetourAttach(&(PVOID&)sg_fnVirtualAlloc, VirtualAlloc_Hook);
		::DetourTransactionCommit();
	}
}

namespace AlphaRomCrack
{
	auto Bypass(Fn_FindCallback_t fnCallback) -> void
	{
		AlphaRomCrack::FindSarcheckDll(fnCallback);
	}
}

