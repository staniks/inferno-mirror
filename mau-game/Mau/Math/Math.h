#ifndef MAU_MATH_H
#define MAU_MATH_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

namespace Mau
{
    constexpr float PI = 3.14159265358979323846f;
    constexpr float DoublePI = static_cast<float>(2.0 * PI);

    template <typename T>
    constexpr const T& Clamp(const T& pValue, const T& pMin, const T& pMax)
    {
        if (pValue < pMin)
        {
            return pMin;
        }
        if (pValue > pMax)
        {
            return pMax;
        }
        return pValue;
    }
}

#endif
