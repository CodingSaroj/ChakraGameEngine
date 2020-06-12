#ifndef CHAKRA_VECTOR_HPP
#define CHAKRA_VECTOR_HPP

#include <iostream>
#include <type_traits>

#include <cassert>

#include "core/math/Functions.hpp"

namespace Chakra
{
    namespace Math
    {
        template <unsigned int size, typename T = float>
        class Vector
        {
            public:
                union
                {
                    T raw[size];

                    struct
                    {
                        T x;
                        std::conditional_t<size >= 2, T, int[0]> y;
                        std::conditional_t<size >= 3, T, int[0]> z;
                        std::conditional_t<size == 4, T, int[0]> w;
                    };

                    struct
                    {
                        T r;
                        std::conditional_t<size >= 2, T, int[0]> g;
                        std::conditional_t<size >= 3, T, int[0]> b;
                        std::conditional_t<size == 4, T, int[0]> a;
                    };

                    struct
                    {
                        T s;
                        std::conditional_t<size >= 2, T, int[0]> t;
                    };
                };

                template <typename... Args>
                Vector(Args... args)
                    : raw{args...}
                {
                    static_assert(size <= 4, "Invalid size passed to Vector.");
                    static_assert(sizeof...(args) == size || sizeof...(args) == 0, "Invalid number of args in constructor of Vector.");

                    if (sizeof...(args) == 0)
                    {
                        for (int i = 0; i < size; i++)
                        {
                            raw[i] = 0;
                        }
                    }
                }

                inline void negate()
                {
                    *this = -(*this);
                }

                T magnitude()
                {
                    T result = 0;

                    for (int i = 0; i < size; i++)
                    {
                        result += raw[i] * raw[i];
                    }

                    return sqrt(result);
                }

                T dot(const Vector<size, T> & vec)
                {
                    T result = 0;

                    for (int i = 0; i < size; i++)
                    {
                        result += raw[i] * vec.raw[i];
                    }

                    return result;
                }

                T cross(const Vector<size, T> & vec)
                {
                    auto noRootMagnitude = [](Vector<size, T> & vec)->T
                    {
                        T result = 0;

                        for (int i = 0; i < size; i++)
                        {
                            result += vec[i] * vec[i];
                        }
                        
                        return result;
                    };

                    T dotVec = dot(vec);

                    return (noRootMagnitude(*this) * noRootMagnitude(vec)) - (dotVec * dotVec);
                }

                T distance(const Vector<size, T> & vec)
                {
                    T sum = 0;

                    for (int i = 0; i < size; i++)
                    {
                        sum += (vec[i] - raw[i]) * (vec[i] - raw[i]);
                    }

                    return sqrt(sum);
                }

                T rdistance(const Vector<size, T> & vec)
                {
                    T sum = 0;

                    for (int i = 0; i < size; i++)
                    {
                        sum += abs(vec[i] - raw[i]);
                    }

                    return sum;
                }

                std::string str()
                {
                    std::string repr("{ ");

                    for (int i = 0; i < size; i++)
                    {
                        repr.append(std::to_string(raw[i]));

                        if (i != size - 1)
                        {
                            repr.append(", ");
                        }
                    }

                    repr.append(" }");

                    return repr;
                }

                T & operator [](unsigned int index)
                {
                    assert(index < size);

                    return raw[index];
                }

                Vector<size, T> operator +(const Vector<size, T> & vec)
                {
                    Vector<size, T> result = *this;

                    for (int i = 0; i < size; i++)
                    {
                        result.raw[i] += vec.raw[i];
                    }

                    return result;
                }

                Vector<size, T> operator -(const Vector<size, T> & vec)
                {
                    Vector<size, T> result = *this;

                    for (int i = 0; i < size; i++)
                    {
                        result.raw[i] -= vec.raw[i];
                    }

                    return result;
                }

                Vector<size, T> operator *(const Vector<size, T> & vec)
                {
                    Vector<size, T> result = *this;

                    for (int i = 0; i < size; i++)
                    {
                        result.raw[i] *= vec.raw[i];
                    }

                    return result;
                }

                Vector<size, T> operator /(const Vector<size, T> & vec)
                {
                    Vector<size, T> result = *this;

                    for (int i = 0; i < size; i++)
                    {
                        result.raw[i] /= vec.raw[i];
                    }
                    
                    return result;
                }

                Vector<size, T> operator +(const T & value)
                {
                    Vector<size, T> result = *this;

                    for (int i = 0; i < size; i++)
                    {
                        result.raw[i] += value;
                    }

                    return result;
                }

                Vector<size, T> operator -(const T & value)
                {
                    Vector<size, T> result = *this;

                    for (int i = 0; i < size; i++)
                    {
                        result.raw[i] -= value;
                    }

                    return result;
                }

                Vector<size, T> operator *(const T & value)
                {
                    Vector<size, T> result = *this;

                    for (int i = 0; i < size; i++)
                    {
                        result.raw[i] *= value;
                    }

                    return result;
                }

                Vector<size, T> operator /(const T & value)
                {
                    Vector<size, T> result = *this;

                    for (int i = 0; i < size; i++)
                    {
                        result.raw[i] /= value;
                    }

                    return result;
                }

                Vector<size, T> operator +=(const Vector<size, T> & vec)
                {
                    return *this = *this + vec;
                }

                Vector<size, T> operator -=(const Vector<size, T> & vec)
                {
                    return *this = *this - vec;
                }

                Vector<size, T> operator *=(const Vector<size, T> & vec)
                {
                    return *this = *this * vec;
                }

                Vector<size, T> operator /=(const Vector<size, T> & vec)
                {
                    return *this = *this / vec;
                }

                Vector<size, T> operator +=(const T & value)
                {
                    return *this = *this + value;
                }

                Vector<size, T> operator -=(const T & value)
                {
                    return *this = *this - value;
                }

                Vector<size, T> operator *=(const T & value)
                {
                    return *this = *this * value;
                }

                Vector<size, T> operator /=(const T & value)
                {
                    return *this = *this / value;
                }

                Vector<size, T> operator -()
                {
                    Vector<size, T> negated = *this;

                    for (int i = 0; i < size; i++)
                    {
                        negated.raw[i] = -raw[i];
                    }
                    
                    return negated;
                }                
        };
    }
}

#endif
