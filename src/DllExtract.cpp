#include <AlphaRomCrack/DllExtract.h>
#include <AlphaRomCrack/SarcheckFinder.h>


namespace AlphaRomCrack
{
	static auto __stdcall SaveSarcheck(LPSarcheckInfo lpInfo) -> void
	{
		::CreateDirectoryW(L"AlphaRomCrack", nullptr);

		const HANDLE hfile = ::CreateFileW(L"AlphaRomCrack\\sarcheck.dll", GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (hfile != INVALID_HANDLE_VALUE)
		{
			DWORD written{};
			bool state = ::WriteFile(hfile, lpInfo->pDllData, lpInfo->nDllSize, &written, nullptr) == TRUE;
			if (state && (written == lpInfo->nDllSize))
			{
				::MessageBoxW(nullptr, L"save sarcheck.dll to AlphaRomCrack\\sarcheck.dll!", L"AlphaRomCrack", MB_OK);
			}
			else
			{
				::MessageBoxW(nullptr, L"save sarcheck.dll failed!", L"AlphaRomCrack", MB_OK);
			}

			::FlushFileBuffers(hfile);
			::CloseHandle(hfile);
		}
		else
		{
			::MessageBoxW(nullptr, L"create file sarcheck.dll failed!", L"AlphaRomCrack", MB_OK);
		}

		::ExitProcess(-1);
	}

	auto ExtractSarcheck() -> void
	{
		AlphaRomCrack::FindSarcheckDll(SaveSarcheck);
	}
}