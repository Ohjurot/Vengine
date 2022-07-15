#include <iostream>
#include <iomanip>
#include <sstream>

#include <Windows.h>
#include <xxhash/xxhash.h>


INT WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
    const char* text = "Hello World!";
    uint64_t text_hash = XXH64(text, strlen(text), 0);

    std::stringstream ss;
    ss << "TEXT: " << text << std::endl << "HASH: " << std::hex << std::showbase << std::setw(16) << text_hash;
    MessageBoxA(NULL, ss.str().c_str(), "", MB_OK);

    return 0;
}
