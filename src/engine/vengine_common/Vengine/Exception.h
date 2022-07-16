#pragma once

#include <exception>
#include <cstring>

#ifndef VENGINE_EXCEPTION_BUFFER_SIZE
#define VENGINE_EXCEPTION_BUFFER_SIZE 512
#endif

namespace vengine
{
    // Base exception
    template<unsigned int Size>
    class TException : public std::exception
    {
        public:
            // Constructors
            TException() noexcept
            {
                m_message[0] = 0x0;
            }
            TException(const char* msg) noexcept
            {
                strcpy_s<Size>(m_message, msg);
            }
            TException(const TException& other) noexcept
            {
                memcpy(m_message, other.m_message, Size);
            }

            // Copy
            TException& operator=(const TException& other) noexcept
            {
                memcpy(m_message, other.m_message, Size);
            }

            char const* what() const override
            {
                return m_message;
            }

        protected:
            // Message buffer of message
            char m_message[Size];
    };

    // Logical exception classes
    template<unsigned int Size>
    class TRecoverableException : public TException<Size>
    {
        public:
            TRecoverableException() noexcept = default;
            TRecoverableException(const char* msg) noexcept :
                TException<Size>(msg)
            {}

    };
    template<unsigned int Size>
    class TCriticalException : public TException<Size>
    {
        public:
            TCriticalException() noexcept = default;
            TCriticalException(const char* msg) noexcept :
                TException<Size>(msg)
            {}
    };
    
    // Exception typedefs
    typedef TException<VENGINE_EXCEPTION_BUFFER_SIZE> Exception;
    typedef TRecoverableException<VENGINE_EXCEPTION_BUFFER_SIZE> RecoverableException;
    typedef TCriticalException<VENGINE_EXCEPTION_BUFFER_SIZE> CriticalException;
}
