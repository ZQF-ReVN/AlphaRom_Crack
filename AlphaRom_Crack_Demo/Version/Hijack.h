#pragma once
#include <Windows.h>
#include <iostream>
#include <Shlwapi.h>
#pragma comment( lib, "Shlwapi.lib")

#pragma comment(linker, "/EXPORT:GetFileVersionInfoA=_AheadLib_GetFileVersionInfoA,@1")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoByHandle=_AheadLib_GetFileVersionInfoByHandle,@2")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExA=_AheadLib_GetFileVersionInfoExA,@3")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExW=_AheadLib_GetFileVersionInfoExW,@4")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeA=_AheadLib_GetFileVersionInfoSizeA,@5")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExA=_AheadLib_GetFileVersionInfoSizeExA,@6")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExW=_AheadLib_GetFileVersionInfoSizeExW,@7")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeW=_AheadLib_GetFileVersionInfoSizeW,@8")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoW=_AheadLib_GetFileVersionInfoW,@9")
#pragma comment(linker, "/EXPORT:VerFindFileA=_AheadLib_VerFindFileA,@10")
#pragma comment(linker, "/EXPORT:VerFindFileW=_AheadLib_VerFindFileW,@11")
#pragma comment(linker, "/EXPORT:VerInstallFileA=_AheadLib_VerInstallFileA,@12")
#pragma comment(linker, "/EXPORT:VerInstallFileW=_AheadLib_VerInstallFileW,@13")
#pragma comment(linker, "/EXPORT:VerLanguageNameA=_AheadLib_VerLanguageNameA,@14")
#pragma comment(linker, "/EXPORT:VerLanguageNameW=_AheadLib_VerLanguageNameW,@15")
#pragma comment(linker, "/EXPORT:VerQueryValueA=_AheadLib_VerQueryValueA,@16")
#pragma comment(linker, "/EXPORT:VerQueryValueW=_AheadLib_VerQueryValueW,@17")


PVOID pfnAheadLib_GetFileVersionInfoA;
PVOID pfnAheadLib_GetFileVersionInfoByHandle;
PVOID pfnAheadLib_GetFileVersionInfoExA;
PVOID pfnAheadLib_GetFileVersionInfoExW;
PVOID pfnAheadLib_GetFileVersionInfoSizeA;
PVOID pfnAheadLib_GetFileVersionInfoSizeExA;
PVOID pfnAheadLib_GetFileVersionInfoSizeExW;
PVOID pfnAheadLib_GetFileVersionInfoSizeW;
PVOID pfnAheadLib_GetFileVersionInfoW;
PVOID pfnAheadLib_VerFindFileA;
PVOID pfnAheadLib_VerFindFileW;
PVOID pfnAheadLib_VerInstallFileA;
PVOID pfnAheadLib_VerInstallFileW;
PVOID pfnAheadLib_VerLanguageNameA;
PVOID pfnAheadLib_VerLanguageNameW;
PVOID pfnAheadLib_VerQueryValueA;
PVOID pfnAheadLib_VerQueryValueW;

HMODULE g_OldModule = NULL;

VOID WINAPI FreeHijack()
{
	if (g_OldModule)
	{
		FreeLibrary(g_OldModule);
	}
}

FARPROC WINAPI GetAddress(PCSTR pszProcName)
{
	FARPROC fpAddress = GetProcAddress(g_OldModule, pszProcName);
	if (fpAddress == NULL)
	{
		MessageBoxW(NULL, L"GetProcAddress Failed!", L"Hijack Dll", MB_OK);
		ExitProcess(0);
	}

	return fpAddress;
}

VOID WINAPI CreateHijack()
{
	WCHAR tzPath[MAX_PATH];
	GetSystemDirectoryW(tzPath, MAX_PATH);
	lstrcatW(tzPath, L"\\version.dll");

	g_OldModule = LoadLibraryW(tzPath);
	if (g_OldModule == NULL)
	{
		MessageBoxW(NULL, L"Load Org Dll Failed!", L"Hijack Dll", MB_OK);
		ExitProcess(0);
	}

	pfnAheadLib_GetFileVersionInfoA = GetAddress("GetFileVersionInfoA");
	pfnAheadLib_GetFileVersionInfoByHandle = GetAddress("GetFileVersionInfoByHandle");
	pfnAheadLib_GetFileVersionInfoExA = GetAddress("GetFileVersionInfoExA");
	pfnAheadLib_GetFileVersionInfoExW = GetAddress("GetFileVersionInfoExW");
	pfnAheadLib_GetFileVersionInfoSizeA = GetAddress("GetFileVersionInfoSizeA");
	pfnAheadLib_GetFileVersionInfoSizeExA = GetAddress("GetFileVersionInfoSizeExA");
	pfnAheadLib_GetFileVersionInfoSizeExW = GetAddress("GetFileVersionInfoSizeExW");
	pfnAheadLib_GetFileVersionInfoSizeW = GetAddress("GetFileVersionInfoSizeW");
	pfnAheadLib_GetFileVersionInfoW = GetAddress("GetFileVersionInfoW");
	pfnAheadLib_VerFindFileA = GetAddress("VerFindFileA");
	pfnAheadLib_VerFindFileW = GetAddress("VerFindFileW");
	pfnAheadLib_VerInstallFileA = GetAddress("VerInstallFileA");
	pfnAheadLib_VerInstallFileW = GetAddress("VerInstallFileW");
	pfnAheadLib_VerLanguageNameA = GetAddress("VerLanguageNameA");
	pfnAheadLib_VerLanguageNameW = GetAddress("VerLanguageNameW");
	pfnAheadLib_VerQueryValueA = GetAddress("VerQueryValueA");
	pfnAheadLib_VerQueryValueW = GetAddress("VerQueryValueW");

}

EXTERN_C __declspec(naked) void __cdecl AheadLib_GetFileVersionInfoA(void)
{
	__asm jmp pfnAheadLib_GetFileVersionInfoA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_GetFileVersionInfoByHandle(void)
{
	__asm jmp pfnAheadLib_GetFileVersionInfoByHandle;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_GetFileVersionInfoExA(void)
{
	__asm jmp pfnAheadLib_GetFileVersionInfoExA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_GetFileVersionInfoExW(void)
{
	__asm jmp pfnAheadLib_GetFileVersionInfoExW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_GetFileVersionInfoSizeA(void)
{
	__asm jmp pfnAheadLib_GetFileVersionInfoSizeA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_GetFileVersionInfoSizeExA(void)
{
	__asm jmp pfnAheadLib_GetFileVersionInfoSizeExA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_GetFileVersionInfoSizeExW(void)
{
	__asm jmp pfnAheadLib_GetFileVersionInfoSizeExW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_GetFileVersionInfoSizeW(void)
{
	__asm jmp pfnAheadLib_GetFileVersionInfoSizeW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_GetFileVersionInfoW(void)
{
	__asm jmp pfnAheadLib_GetFileVersionInfoW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_VerFindFileA(void)
{
	__asm jmp pfnAheadLib_VerFindFileA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_VerFindFileW(void)
{
	__asm jmp pfnAheadLib_VerFindFileW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_VerInstallFileA(void)
{
	__asm jmp pfnAheadLib_VerInstallFileA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_VerInstallFileW(void)
{
	__asm jmp pfnAheadLib_VerInstallFileW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_VerLanguageNameA(void)
{
	__asm jmp pfnAheadLib_VerLanguageNameA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_VerLanguageNameW(void)
{
	__asm jmp pfnAheadLib_VerLanguageNameW;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_VerQueryValueA(void)
{
	__asm jmp pfnAheadLib_VerQueryValueA;
}

EXTERN_C __declspec(naked) void __cdecl AheadLib_VerQueryValueW(void)
{
	__asm jmp pfnAheadLib_VerQueryValueW;
}