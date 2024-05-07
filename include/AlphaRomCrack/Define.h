#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>


namespace AlphaRomCrack
{
	typedef struct SarcheckInfo
	{
		LPCSTR cpDllName;
		PDWORD pDllData;
		DWORD nDllSize;
	}*LPSarcheckInfo;

	using Fn_FindCallback_t = void(__stdcall*)(LPSarcheckInfo);
	using Fn_VirtualAlloc_t = decltype(&::VirtualAlloc);
}