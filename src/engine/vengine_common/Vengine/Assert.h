#pragma once

#include <Vengine/Annotations.h>
#include <Vengine/String/PlacedStringStream.h>

#include <fmt/format.h>

#include <cstring>
#include <cstdarg>

#include <Windows.h>
#include <debugapi.h>

// Abstraction
#define _VENGINE_ASSERT_FORMAT_BASE "Runtime Asserstion Failed!\n{}\nFile: {}\nLine: {}\nExpression: {}"
#if defined(VENGINE_CONF_DEBUG) || defined(VENGINE_CONF_DEVELOPMENT)
#define _VENGINE_ASSERT_FORMAT _VENGINE_ASSERT_FORMAT_BASE"\n\nContinue? Press Cancel to Debug."
#define _VENGINE_ASSERT_STOP(msg) \
{\
auto _result = MessageBoxA(NULL, msg, "Assertion Failed", MB_YESNOCANCEL | MB_ICONERROR);\
switch(_result) \
{ \
    case IDYES: \
        break; \
    case IDCANCEL: \
        DebugBreak(); \
        break; \
    case IDNO: \
        [[fallthrough]];\
    default: \
        break; \
} \
}
#else
#define _VENGINE_ASSERT_FORMAT _VENGINE_ASSERT_FORMAT_BASE"\n\nThe Application will close now!"
#define _VENGINE_ASSERT_STOP(msg) \
{\
MessageBoxA(NULL, msg, "Assertion Failed", MB_OK | MB_ICONERROR);\
DebugBreak(); // TODO: REPLACE WITH STOP APP \ 
}
#endif


// Symbols
#define _VENGINE_ASSERT_STR(w) #w
#define _VENGINE_ASSERT_MESSAGE _assertMessage
#define _VENGINE_FASSERT_MESSAGE _fassertMessage
#define _VENGINE_ASSERT_SIZE 512

// Functionality
#define _VENGINE_ASSERT_RAIS(expr, msg) \
char _VENGINE_ASSERT_MESSAGE[_VENGINE_ASSERT_SIZE] = {0x0}; \
_VENGINE_ASSERT_MESSAGE[fmt::format_to_n(_VENGINE_ASSERT_MESSAGE, _VENGINE_ASSERT_SIZE - 1, \
    _VENGINE_ASSERT_FORMAT, \
    msg, __FILE__, __LINE__, _VENGINE_ASSERT_STR(expr)).size] = 0x0; \
_VENGINE_ASSERT_STOP(_VENGINE_ASSERT_MESSAGE);
#define _VENGINE_ASSERT_RAW(expr, msg) \
if(!(expr)) \
{ \
    _VENGINE_ASSERT_RAIS(expr, msg); \
}
#define _VENGINE_F_ASSERT_RAW(expr, f, ...) \
if(!(expr)) \
{ \
    char _VENGINE_FASSERT_MESSAGE[_VENGINE_ASSERT_SIZE];\
    _VENGINE_FASSERT_MESSAGE[fmt::format_to_n(_VENGINE_FASSERT_MESSAGE, _VENGINE_ASSERT_SIZE - 1, f, __VA_ARGS__).size] = 0x0; \
    _VENGINE_ASSERT_RAIS(expr, _VENGINE_FASSERT_MESSAGE); \
}

// Proper assertion
#if defined(VENGINE_CONF_SHIPPING)
// SHIPPING
#define VENGINE_RUNTIME_ASSERT(expr, msg)           _VENGINE_ASSERT_RAW(expr, msg)
#define VENGINE_ASSERT(expr, msg)
#define VENGINE_DEBUG_ASSERT(expr, msg)
#define VENGINE_RUNTIME_F_ASSERT(expr, msg, ...)    _VENGINE_F_ASSERT_RAW(expr, msg, __VA_ARGS__)
#define VENGINE_F_ASSERT(expr, msg, ...)            
#define VENGINE_DEBUG_F_ASSERT(expr, msg, ...)      
#elif defined(VENGINE_CONF_DEVELOPMENT)
// DEVELOPMENT
#define VENGINE_RUNTIME_ASSERT(expr, msg)           _VENGINE_ASSERT_RAW(expr, msg)
#define VENGINE_ASSERT(expr, msg)                   _VENGINE_ASSERT_RAW(expr, msg)
#define VENGINE_DEBUG_ASSERT(expr, msg)
#define VENGINE_RUNTIME_F_ASSERT(expr, msg, ...)    _VENGINE_F_ASSERT_RAW(expr, msg, __VA_ARGS__)
#define VENGINE_F_ASSERT(expr, msg, ...)            _VENGINE_F_ASSERT_RAW(expr, msg, __VA_ARGS__)
#define VENGINE_DEBUG_F_ASSERT(expr, msg, ...)      
#elif defined(VENGINE_CONF_DEBUG)
// DEBUG
#define VENGINE_RUNTIME_ASSERT(expr, msg)           _VENGINE_ASSERT_RAW(expr, msg)
#define VENGINE_ASSERT(expr, msg)                   _VENGINE_ASSERT_RAW(expr, msg)
#define VENGINE_DEBUG_ASSERT(expr, msg)             _VENGINE_ASSERT_RAW(expr, msg)
#define VENGINE_RUNTIME_F_ASSERT(expr, msg, ...)    _VENGINE_F_ASSERT_RAW(expr, msg, __VA_ARGS__)
#define VENGINE_F_ASSERT(expr, msg, ...)            _VENGINE_F_ASSERT_RAW(expr, msg, __VA_ARGS__)
#define VENGINE_DEBUG_F_ASSERT(expr, msg, ...)      _VENGINE_F_ASSERT_RAW(expr, msg, __VA_ARGS__)
#endif

