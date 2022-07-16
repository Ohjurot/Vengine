#pragma once

#include <Vengine/Annotations.h>
#include <Vengine/String/PlacedStringStream.h>

#include <fmt/format.h>

#include <cstring>
#include <cstdarg>

#include <Windows.h>
#include <debugapi.h>

// Abstraction
#define _VENGINE_ASSERT_NOTIFY(msg) MessageBoxA(NULL, msg, "Assertion Failed", MB_OK | MB_ICONERROR)
#define _VENGINE_ASSERT_BREAK() DebugBreak()

// Symbols
#define _VENGINE_ASSERT_STR(w) #w
#define _VENGINE_ASSERT_MESSAGE _assertMessage
#define _VENGINE_ASSERT_SIZE 512

// Functionality
#define _VENGINE_ASSERT_RAIS(expr, msg) \
char _VENGINE_ASSERT_MESSAGE[_VENGINE_ASSERT_SIZE] = {0x0}; \
_VENGINE_ASSERT_MESSAGE[fmt::format_to_n(_VENGINE_ASSERT_MESSAGE, _VENGINE_ASSERT_SIZE - 1, \
    "Runtime Asserstion Failed!\n{}\nFile: {}\nLine: {}\nExpression: {}", \
    msg, __FILE__, __LINE__, _VENGINE_ASSERT_STR(expr)).size] = 0x0; \
_VENGINE_ASSERT_NOTIFY(_VENGINE_ASSERT_MESSAGE); \
_VENGINE_ASSERT_BREAK();
#define _VENGINE_ASSERT_RAW(expr, msg) \
if(!(expr)) \
{ \
    _VENGINE_ASSERT_RAIS(expr, msg) \
}

// Proper assertion
#if defined(VENGINE_CONF_SHIPPING)
// SHIPPING
#define VENGINE_RUNTIME_ASSERT(expr, msg)   _VENGINE_ASSERT_RAW(expr, msg)
#define VENGINE_ASSERT(expr, msg)
#define VENGINE_DEBUG_ASSERT(expr, msg)
#elif defined(VENGINE_CONF_DEVELOPMENT)
// DEVELOPMENT
#define VENGINE_RUNTIME_ASSERT(expr, msg)   _VENGINE_ASSERT_RAW(expr, msg)
#define VENGINE_ASSERT(expr, msg)           _VENGINE_ASSERT_RAW(expr, msg)
#define VENGINE_DEBUG_ASSERT(expr, msg)
#elif defined(VENGINE_CONF_DEBUG)
// DEBUG
#define VENGINE_RUNTIME_ASSERT(expr, msg)   _VENGINE_ASSERT_RAW(expr, msg)
#define VENGINE_ASSERT(expr, msg)           _VENGINE_ASSERT_RAW(expr, msg)
#define VENGINE_DEBUG_ASSERT(expr, msg)     _VENGINE_ASSERT_RAW(expr, msg)
#endif

