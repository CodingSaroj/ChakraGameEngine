#ifndef CHAKRA_CORE_ENDIAN_HPP
#define CHAKRA_CORE_ENDIAN_HPP

#include "core/Common.hpp"

namespace Chakra
{
    namespace Endian
    {
        enum class Endian
        {
            Little,
            Big
        };

        inline Endian GetSystemEndian()
        {
            uint32_t i = 1;

            return ((char *)&i)[0] ? Endian::Little : Endian::Big;
        }

        template <typename Type>
        void ByteSwap(Type & data)
        {
            auto & raw = *(std::array<uint8_t, sizeof(Type)> *)&data;

            std::reverse(raw.begin(), raw.end());
        }

        template <typename Type>
        Type SystemToLittle(Type value)
        {
            if (GetSystemEndian() == Endian::Big)
            {
                ByteSwap(value);
            }
            
            return value;
        }

        template <typename Type>
        Type LittleToSystem(Type value)
        {
            if (GetSystemEndian() == Endian::Big)
            {
                ByteSwap(value);
            }

            return value;
        }
    }
}

#endif
