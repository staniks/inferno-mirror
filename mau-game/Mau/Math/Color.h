#ifndef MAU_COLOR_H
#define MAU_COLOR_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Base/Types.h"

namespace Mau
{
#pragma pack(push, 1)
    struct Color
    {
        byte r, g, b, a;

        inline bool operator==(const Color& pColor) const;

        inline uint32 ToUint32() const;

        inline static Color AlphaBlend(const Color& pSrcColor, const Color& pDstColor);
    };
#pragma pack(pop)

    inline bool Color::operator==(const Color& pColor) const
    {
        return r == pColor.r && g == pColor.g && b == pColor.b && a == pColor.a;
    };

    inline Color Color::AlphaBlend(const Color& pSrcColor, const Color& pDstColor)
    {
        const int32 alpha = pSrcColor.a + 1;
        const int32 inverseAlpha = 256 - pSrcColor.a;

        return Color
        {
            byte((pSrcColor.r * alpha + pDstColor.r * inverseAlpha) >> 8),
            byte((pSrcColor.g * alpha + pDstColor.g * inverseAlpha) >> 8),
            byte((pSrcColor.b * alpha + pDstColor.b * inverseAlpha) >> 8),
            255
        };
    }

    inline uint32 Color::ToUint32() const
    {
        // Forgive me, father, for I have sinned
        return *reinterpret_cast<uint32*>(const_cast<Color*>(this));
    }
}

#endif
