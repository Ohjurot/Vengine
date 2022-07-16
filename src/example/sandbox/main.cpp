#include <iostream>
#include <iomanip>
#include <sstream>

#include <Vengine/Assert.h>

#include <Windows.h>

INT WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
    VENGINE_ASSERT(false, "This is a test");

    return 0;
}
