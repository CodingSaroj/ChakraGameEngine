#ifndef CHAKRA_MATRIX_HPP
#define CHAKRA_MATRIX_HPP

#include <tuple>

#include "core/math/Functions.hpp"
#include "core/math/Vector.hpp"

namespace Chakra
{
    namespace Math
    {
        template <unsigned int x, unsigned int y, typename T = float>
        class Matrix
        {
            public:
                union
                {
                    T raw[x][y];
                    Vector<y, T> rawVec[x];
                };

                template <typename... Args>
                Matrix(Args... args)
                    : raw{args...}
                {
                    static_assert(x <= 4, "Invalid x size for Matrix.");
                    static_assert(y <= 4, "Invalid y size for Matrix.");
                    static_assert(sizeof...(args) == x * y || sizeof...(args) == 0, "Invalid arguments to constructor of Matrix.");

                    if (sizeof...(args) == 0)
                    {
                        for (int i = 0; i < y; i++)
                        {
                            for (int j = 0; j < x; j++)
                            {
                                raw[j][i] = 0;
                            }
                        }
                    }
                }

                void translate(const Vector<3, T> & vec)
                {
                    static_assert(std::is_same_v<T, float> || std::is_same_v<T, double>, "Cannot rotate a Matrix of integers.");
                    static_assert(x == 4 && y == 4, "Cannot translate a Matrix that isn't 4x4.");

                    raw[3][0] += vec.x;
                    raw[3][1] += vec.y;
                    raw[3][2] += vec.z;
                    raw[3][3] = 1;
                }

                void rotate(const Vector<3, T> & axis, float angle)
                {
                    static_assert(std::is_same_v<T, float> || std::is_same_v<T, double>, "Cannot rotate a Matrix of integers.");
                    static_assert(x == 4 && y == 4, "Cannot rotate a Matrix that isn't 4x4.");

                    Matrix<4, 4, T> rot;
                    T sinAngle = sin(angle);
                    T cosAngle = cos(angle);

                    rot[0][0] = cosAngle + (axis.x * axis.x * (1 - cosAngle));
                    rot[1][0] = (axis.x * axis.y * (1 - cosAngle)) - (axis.z * sinAngle);
                    rot[2][0] = (axis.x * axis.z * (1 - cosAngle)) + (axis.y * sinAngle);

                    rot[0][1] = (axis.y * axis.x * (1 - cosAngle)) + (axis.z * sinAngle);
                    rot[1][1] = cosAngle + (axis.y * axis.y * (1 - cosAngle));
                    rot[2][1] = (axis.y * axis.z * (1 - cosAngle)) - (axis.x * sinAngle);

                    rot[0][2] = (axis.z * axis.x * (1 - cosAngle)) - (axis.y * sinAngle);
                    rot[1][2] = (axis.z * axis.y * (1 - cosAngle)) + (axis.x * sinAngle);
                    rot[2][2] = cosAngle + (axis.z * axis.z * (1 - cosAngle));

                    *this *= rot;
                }

                void scale(const Vector<3, T> & vec)
                {
                    static_assert(std::is_same_v<T, float> || std::is_same_v<T, double>, "Cannot scale a Matrix of integers.");
                    static_assert(x == 4 && y == 4, "Cannot scale a Matrix that isn't 4x4.");

                    raw[0][0] *= vec.x;
                    raw[1][1] *= vec.y;
                    raw[2][2] *= vec.z;
                    raw[3][3] = 1;
                }

                void ortho(T top, T bottom, T left, T right, T near, T far)
                {
                    static_assert(std::is_same_v<T, float> || std::is_same_v<T, double>, "Cannot generate a projection matrix of integers.");
                    static_assert(x == 4 && y == 4, "Cannot generate a projection matrix that isn't 4x4.");

                    T width        = right - left;
                    T height       = bottom - top;
                    T farMinusNear = far - near;

                    raw[0][0] = 1.0 / width;
                    raw[1][1] = 1.0 / height;
                    raw[2][2] = 1.0 / farMinusNear;
                    raw[3][2] = -near / farMinusNear;
                    raw[3][3] = 1.0;
                }

                void perspective(T fov, T aspect, T near, T far)
                {
                    static_assert(std::is_same_v<T, float> || std::is_same_v<T, double>, "Cannot generate a projection matrix of integers.");
                    static_assert(x == 4 && y == 4, "Cannot generate a projection matrix that isn't 4x4.");

                    T tanFovBy2    = tan(fov / 2);
                    T farMinusNear = far - near;

                    raw[0][0] = 1.0 / aspect * tanFovBy2;
                    raw[1][1] = 1.0 / tanFovBy2;
                    raw[2][2] = (far + near) / farMinusNear;
                    raw[2][3] = -1.0;
                    raw[3][2] = (2 * far * near) / farMinusNear;
                    raw[3][3] = 0.0;
                }

                std::string str()
                {
                    std::string repr("{ ");

                    for (int i = 0; i < x; i++)
                    {
                        for (int j = 0; j < y; j++)
                        {
                            repr.append(std::to_string(raw[i][j]));

                            if (j != x - 1)
                            {
                                repr.append(", ");
                            }
                        }

                        repr.append(" }\n");

                        if (i != y - 1)
                        {
                            repr.append("{ ");
                        }
                    }

                    return repr;
                }

                Vector<y, T> & operator [](unsigned int index)
                {
                    assert(index < x);

                    return rawVec[index];
                }

                Matrix<x, y, T> operator +(Matrix<x, y, T> & mat)
                {
                    Matrix<x, y, T> result = *this;

                    for (int i = 0; i < x; i++)
                    {
                        for (int j = 0; j < y; j++)
                        {
                            result[x][y] += mat[x][y];
                        }
                    }

                    return result;
                }

                Matrix<x, y, T> operator -(Matrix<x, y, T> & mat)
                {
                    Matrix<x, y, T> result = *this;

                    for (int i = 0; i < x; i++)
                    {
                        for (int j = 0; j < y; j++)
                        {
                            result[x][y] -= mat[x][y];
                        }
                    }

                    return result;
                }

                template <unsigned int x1, unsigned int y1>
                Matrix<x1, y, T> operator *(Matrix<x1, y1, T> & mat)
                {
                    static_assert(x == y1 && y == x1, "Incompatible Matrix-Matrix multiplication.");

                    Matrix<x1, y, T> result;

                    for (int i = 0; i < y; i++)
                    {
                        for(int j = 0; j < x1; j++)
                        {
                            for (int k = 0; k < x; k++)
                            {
                                result[j][i] += raw[k][i] * mat[j][k];
                            }
                        }
                    }

                    return result;
                }

                template <unsigned int size>
                Vector<size, T> operator *(Vector<size, T> & vec)
                {
                    static_assert(x == size, "Incompatible Matrix-Vector multiplication.");

                    Vector<size, T> result;

                    for (int i = 0; i < y; i++)
                    {
                        for (int j = 0; j < x; j++)
                        {
                            result[i] += raw[i][j] * vec[j];
                        }
                    }

                    return result;
                }

                Matrix<x, y, T> operator +(const T & value)
                {
                    Matrix<x, y, T> result = *this;

                    for (int i = 0; i < x; i++)
                    {
                        for (int j = 0; j < y; j++)
                        {
                            result[i][j] += value;
                        }
                    }

                    return result;
                }

                Matrix<x, y, T> operator -(const T & value)
                {
                    Matrix<x, y, T> result = *this;

                    for (int i = 0; i < x; i++)
                    {
                        for (int j = 0; j < y; j++)
                        {
                            result[i][j] -= value;
                        }
                    }

                    return result;
                }

                Matrix<x, y, T> operator *(const T & value)
                {
                    Matrix<x, y, T> result = *this;

                    for (int i = 0; i < x; i++)
                    {
                        for (int j = 0; j < y; j++)
                        {
                            result[i][j] *= value;
                        }
                    }

                    return result;
                }

                Matrix<x, y, T> operator /(const T & value)
                {
                    Matrix<x, y, T> result = *this;

                    for (int i = 0; i < x; i++)
                    {
                        for (int j = 0; j < y; j++)
                        {
                            result[i][j] /= value;
                        }
                    }

                    return result;
                }

                Matrix<x, y, T> operator +=(Matrix<x, y, T> & mat)
                {
                    return *this = *this + mat;
                }

                Matrix<x, y, T> operator -=(Matrix<x, y, T> & mat)
                {
                    return *this = *this - mat;
                }

                template<unsigned int x1, unsigned int y1>
                Matrix<x, y, T> operator *=(Matrix<x1, y1, T> & mat)
                {
                    return *this = *this * mat;
                }

                template<unsigned int size>
                Matrix<x, y, T> operator *=(Vector<size, T> & vec)
                {
                    return *this = *this * vec;
                }

                Matrix<x, y, T> operator +=(const T & value)
                {
                    return *this = *this + value;
                }

                Matrix<x, y, T> operator -=(const T & value)
                {
                    return *this = *this - value;
                }

                Matrix<x, y, T> operator *=(const T & value)
                {
                    return *this = *this * value;
                }

                Matrix<x, y, T> operator /=(const T & value)
                {
                    return *this = *this / value;
                }
        };
    }
}

#endif
