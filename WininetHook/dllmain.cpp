// dllmain.cpp : Define el punto de entrada de la aplicación DLL.
#include "pch.h"
#include <Windows.h>
#include <wininet.h>
#include <Detours/detours.h>
#include <iostream>


typedef BOOL(__stdcall* PInternetGetConnectedState)(LPDWORD lpdwFlags, DWORD dwReserved);

PInternetGetConnectedState original = nullptr; 

BOOL __stdcall HOOKFUNC(LPDWORD lpdwFlags, DWORD dwReserved) {

    std::cout << "Inside hook" << std::endl;
    return FALSE;

}

bool installhooks() {
	DetourRestoreAfterWith();
	DetourTransactionBegin();

    HMODULE dlladress = GetModuleHandle(L"wininet.dll");

    std::cout << "Obteniendo direccion de wininet.dll" << dlladress <<std::endl;

    original = (PInternetGetConnectedState) GetProcAddress(dlladress, "InternetGetConnectedState");

    std::cout << "Obteniendo direccion de InternetgetConnectedState " << original << std::endl;

	DetourUpdateThread(GetCurrentThread());

	DetourAttach(&(PVOID&)original, HOOKFUNC);

 
    return ERROR_SUCCESS == DetourTransactionCommit();
}
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{

	if (DetourIsHelperProcess()) {
		return TRUE;
	}
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		return installhooks();
		
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:

		return installhooks();
		break;
	}
	return TRUE;
}