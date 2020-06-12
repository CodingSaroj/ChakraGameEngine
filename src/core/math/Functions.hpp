#ifndef CHAKRA_FUNCTIONS_HPP
#define CHAKRA_FUNCTIONS_HPP

#include <cmath>

#include "core/math/Constants.hpp"
#include "core/math/Angles.hpp"

namespace Chakra
{
    namespace Math
    {
        template <typename T>
        T sin(T radians)
        {
            return ::sin(radians);
        }

        template <typename T>
        T cos(T radians)
        {
            return ::cos(radians);
        }

        template <typename T>
        T tan(T radians)
        {
            return ::tan(radians);
        }

        template <typename T>
        T sec(T radians)
        {
            return 1.0 / ::sin(radians);
        }

        template <typename T>
        T cosec(T radians)
        {
            return 1.0 / ::cos(radians);
        }

        template <typename T>
        T cot(T radians)
        {
            return 1.0 / ::tan(radians);
        }

        template <typename T>
        T abs(T number)
        {
            if (number < 0)
            {
                return -number;
            }
            else
            {
                return number;
            }
        }

        template <typename T>
        T round(T number)
        {
            return ::round(number);
        }

        template <typename T1, typename T2>
        T1 pow(T1 number, T2 exponent)
        {
            if (exponent == 0)
            {
                return 1;
            }
            else if (exponent == 1)
            {
                return number;
            }
            else
            {
                T1 result = number;

                while (exponent > 1)
                {
                    result *= result;
                    exponent--;
                }
            }
        }

        template <typename T>
        T sqrt(T number)
        {
            return ::sqrt(number);
        }

        template <typename T>
        T log(T number)
        {
            return ::log(number);
        }

        template <typename T>
        T fact(T number)
        {
            T result = 1;

            for (int i = 1; i <= number; i++)
            {
                result *= i;
            }

            return result;
        }
    }
}

#endif
