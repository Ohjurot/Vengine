#include <iostream>
#include <iomanip>
#include <sstream>

#include <Vengine/Assert.h>
#include <Vengine/Exception.h>

#include <Windows.h>

INT WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
    try
    {
        try
        {
            throw vengine::CriticalException("RC");
        }
        catch (vengine::RecoverableException& cex)
        {
            VENGINE_ASSERT(false, "Recover");
        }
    }
    catch (vengine::Exception& cex)
    {
        VENGINE_ASSERT(false, "Normal");
    }

    return 0;
}
