#include "main.h"
#include <iostream>
#include <Detours/detours.h>

typedef int (*CalculatorFunc)();

CalculatorFunc originalCalculator = nullptr;

int HookedCalculator() {
    std::cout << "Hooked Calculator called!" << std::endl;
    return 34;
}


bool InstallHooks() {

    HMODULE hModule = GetModuleHandle(L"Project1.dll");

    std::cout << "Direccion de memoria del DLL" << std::endl;

    originalCalculator = (CalculatorFunc) GetProcAddress(hModule, "calculator");
  

    DetourUpdateThread(GetCurrentThread());

    DetourAttach(&(PVOID&)originalCalculator, HookedCalculator);


     return ERROR_SUCCESS == DetourTransactionCommit();
       
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        std::cout << "Injected DLL on process" << std::endl;
        return InstallHooks();
  
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
