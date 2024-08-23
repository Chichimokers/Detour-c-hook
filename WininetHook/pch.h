// pch.h: este es un archivo de encabezado precompilado.
// Los archivos que se muestran a continuación se compilan solo una vez, lo que mejora el rendimiento de la compilación en futuras compilaciones.
// Esto también afecta al rendimiento de IntelliSense, incluida la integridad del código y muchas funciones de exploración del código.
// Sin embargo, los archivos que se muestran aquí se vuelven TODOS a compilar si alguno de ellos se actualiza entre compilaciones.
// No agregue aquí los archivos que se vayan a actualizar con frecuencia, ya que esto invalida la ventaja de rendimiento.

#pragma once // Usa directiva #pragma once para evitar inclusiones múltiples
#ifdef HOOKDLL_EXPORTS
#define HOOKDLL_API __declspec(dllexport)
#else
#define HOOKDLL_API __declspec(dllimport)
#endif

#include <Windows.h> // Incluye encabezados de sistema primero

// Incluye encabezados de proyecto después de los de sistema
#include "framework.h" 

extern "C" { // Usa bloques extern "C" para asegurar la compatibilidad con C
    HOOKDLL_API BOOL WINAPI HOOKFUNC(LPDWORD lpdwFlags, DWORD dwReserved); // Usa WINAPI para coincidir con la convención de llamada
    HOOKDLL_API bool installhooks();
    HOOKDLL_API BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);
}
