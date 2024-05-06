#include <AlphaRomCrack/SarcheckFinder.h>
#include <detours.h>

namespace AlphaRomCheck
{
	static bool sg_isCheck = true;
	static Fn_FindCallback_t sg_fnFindCallback;
	static Fn_VirtualAlloc_t sg_fnVirtualAlloc = ::VirtualAlloc;
	static LPVOID sg_aAddressTable[100]{};


	static auto PushAddress(LPVOID lpAddress) -> void
	{
		for (auto& address : sg_aAddressTable)
		{
			if ((address == nullptr) || (address == lpAddress))
			{
				address = lpAddress;
				return;
			}
		}
	}

	static auto QuerySarcheck() -> LPSarcheckInfo
	{
		MEMORY_BASIC_INFORMATION info{};

		for (auto& address : sg_aAddressTable)
		{
			if (address == nullptr) { return nullptr; }

			LPSarcheckInfo info_ptr = (SarcheckInfo*)address;
			if (!::VirtualQuery(info_ptr->cpDllName, &info, sizeof(info))) { continue; }
			if (!(info.Type == MEM_IMAGE && info.State == MEM_COMMIT && info.AllocationProtect == PAGE_EXECUTE_WRITECOPY)) { continue; }
			if (::strncmp("sarcheck.dll", info_ptr->cpDllName, 13)) { continue; }
			if (!info_ptr->pDllData) { continue; }
			if (((PIMAGE_DOS_HEADER)info_ptr->pDllData)->e_magic != IMAGE_DOS_SIGNATURE) { continue; }
			return info_ptr;
		}

		return nullptr;
	}

	static LPVOID WINAPI VirtualAlloc_Hook(LPVOID lpAddress, SIZE_T dwSize, DWORD  flAllocationType, DWORD  flProtec)
	{
		LPVOID buffer_address = sg_fnVirtualAlloc(lpAddress, dwSize, flAllocationType, flProtec);

		if (sg_isCheck) 
		{ 
			if (buffer_address && (dwSize > 8) && (flAllocationType == MEM_COMMIT) && (flProtec == PAGE_READWRITE))
			{
				PushAddress(buffer_address);
			}

			LPSarcheckInfo info_ptr = QuerySarcheck();
			if (info_ptr != nullptr)
			{
				sg_fnFindCallback(info_ptr);
				sg_isCheck = false;
			}
		}

		return buffer_address;
	}

	auto FindSarcheckDll(Fn_FindCallback_t fnCallback) -> void
	{
		sg_fnFindCallback = fnCallback;

		::DetourRestoreAfterWith();
		::DetourTransactionBegin();
		::DetourUpdateThread(GetCurrentThread());
		::DetourAttach(&(PVOID&)sg_fnVirtualAlloc, VirtualAlloc_Hook);
		::DetourTransactionCommit();
	}


}
