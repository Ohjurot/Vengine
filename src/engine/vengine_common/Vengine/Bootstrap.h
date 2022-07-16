#pragma once

#include <Vengine/Annotations.h>
#include <Vengine/Assert.h>

#define VENGINE_IMPLEMENT_MAIN() \
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) \
{ \
    vengine::AppInfo info; \
    /* VENGINE_RUNTIME_ASSERT(VengineOSInit(info, hInstance, lpCmdLine, nShowCmd), "Failed to initialize OS libs"); */ \
    int return_code = ::VengineMain(info); \
    /* VengineOSShutdown(info); */ \
    return return_code; \
}

namespace vengine
{
    // OS Enum
    enum class OS
    {
        // Windows x64 desktop (win64 no gdk)
        Windows_x64,
    };

    // Metadata about the application
    struct AppInfo
    {
        // Type of OS the app is running in
        OS osEnvironment;
    };
}

// Vengine main function to be implemented by game
int VengineMain(const vengine::AppInfo& _v_in_ info);
// Vengine OS state functions to be implement by HAL
bool VengineOSInit(vengine::AppInfo& _v_in_ info, ...);
void VengineOSShutdown(const vengine::AppInfo& _v_in_ info);
