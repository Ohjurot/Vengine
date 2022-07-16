#pragma once

#include <Vengine/Annotations.h>

#include <type_traits>
#include <cstring>

namespace vengine::string
{
    // Length of string
    inline size_t Strlen(const char* _v_in_ string)
    {
        return ::strlen(string);
    }
    inline size_t Strlen(const wchar_t* _v_in_ string)
    {
        return ::wcslen(string);
    }
}
