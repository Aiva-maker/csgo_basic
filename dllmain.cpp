// dllmain.cpp : Defines the entry point for the DLL application.

#include <Windows.h>
#include "helper/utils.hpp"
#include "valve_sdk/sdk.hpp"


DWORD APIENTRY OnDllAttach(LPVOID base)
{
    while (!GetModuleHandleA("serverbrowser.dll")) //sleep until all modules have been loaded
        Sleep(1000);                               //serverbrowser.dll being the last module

#ifdef _DEBUG
    Utils::AttachConsole();
    return true;
#endif

    try {
        Utils::ConsolePrint("Initializing...\n");
        Interfaces::Initialize();
        Interfaces::Dump();

        FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);
    }
    catch (const std::exception& ex) {
        Utils::ConsolePrint("An error occured during initialization:\n");
        Utils::ConsolePrint("%s\n", ex.what());
        Utils::ConsoleReadKey();
        Utils::DetachConsole();
        FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);
    }
}

BOOL APIENTRY OnDllDetach()
{
    Utils::DetachConsole();
    return true;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, OnDllAttach, hModule, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        if (lpReserved == nullptr)
            return OnDllDetach();
        return TRUE;

    default:
        return TRUE;
    }
}

