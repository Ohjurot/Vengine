#pragma once

#include <Vengine/Annotations.h>
#include <Vengine/String/Util.h>

#include <fmt/format.h>

#include <type_traits>
#include <algorithm>
#include <cstring>

namespace vengine
{
    // Custom string stream
    template<typename _v_in_ ST = char, typename = std::enable_if_t<
        std::is_same_v<ST, char> || 
        std::is_same_v<ST, wchar_t> 
    >>
    class PlacedStringStream
    {
        public:
            // Construct
            PlacedStringStream() noexcept = default;
            PlacedStringStream(const PlacedStringStream&) noexcept = delete;
            PlacedStringStream(const PlacedStringStream&& other) noexcept 
            {
                // Set this
                m_buffer = other.m_buffer;
                m_maxSize = other.m_maxSize;
                m_head = other.m_head;

                // Invalidate other
                other.~PlacedStringStream();
            }
            PlacedStringStream(ST* _v_in_ buffer, size_t _v_in_ bufferCharCount) noexcept :
                m_buffer(buffer),
                m_maxSize(bufferCharCount - 1)
            {
                m_head = string::Strlen(buffer);
            }

            // Destruct
            ~PlacedStringStream() noexcept
            {
                m_buffer = nullptr;
                m_maxSize = 0;
                m_head = 0;
            }

            // Copy / Move
            PlacedStringStream& operator=(const PlacedStringStream&) noexcept = delete;
            PlacedStringStream& operator=(const PlacedStringStream&& other) noexcept
            {
                PlacedStringStream::PlacedStringStream(std::move(other));
            }

            // Append string type
            void Append(const ST* _v_in_ str)
            {
                size_t stringLen = string::Strlen(str);
                size_t copyOff = m_head;
                size_t copyLen = std::min<size_t>(stringLen, m_maxSize - m_head);
                if (copyLen)
                {
                    memcpy(&m_buffer[copyOff], str, sizeof(ST) * copyLen);
                    m_buffer[std::min<size_t>(copyOff + copyLen, m_maxSize - 1)] = 0x0;
                    m_head += copyLen;
                }
            }

            // Formated append
            template<typename... AT>
            void AppendF(const ST* _v_in_ fmt, AT&... args)
            {
                fmt::format_to_n_result fmtResult = fmt::format_to_n(&m_buffer[m_head], m_maxSize - m_head, args...);
                m_head += fmtResult.size;
            }

            // Stream operators
            PlacedStringStream& operator<<(const char* msg)
            {
                Append(msg);
                return *this;
            }

        private:
            // Char buffer
            ST* m_buffer = nullptr;

            // Size properties
            size_t m_maxSize = 0;
            size_t m_head = 0;
    };
}
