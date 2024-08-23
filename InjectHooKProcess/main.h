#include <Windows.h>

#ifdef HOOKDLL_EXPORTS
#define HOOKDLL_API __declspec(dllexport)
#else
#define HOOKDLL_API __declspec(dllimport)
#endif

extern "C" HOOKDLL_API bool InstallHooks();

extern "C" HOOKDLL_API int HookedCalculator();