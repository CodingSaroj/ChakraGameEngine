#ifndef CHAKRA_ANGLES_HPP
#define CHAKRA_ANGLES_HPP

#include "core/math/Constants.hpp"

namespace Chakra
{
    namespace Math
    {
        template <typename T>
        T Deg2Rad(T degrees)
        {
            static_assert(std::is_same_v<T, float> || std::is_same_v<T, double>, "Angles can't be in integers.");
            return degrees * (PI / 180);
        }

        template <typename T>
        T Rad2Deg(T radians)
        {
            static_assert(std::is_same_v<T, float> || std::is_same_v<T, double>, "Angles can't be in integers.");
            return radians * (180 / PI);
        }
    }
}

#endif
