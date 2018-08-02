#ifndef MAU_RECT_H
#define MAU_RECT_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Math/Vec2.h"

namespace Mau
{
    struct Rect
    {
    public:
        Rect(Vec2<float> pPosition, Vec2<float> pSize);

        Vec2<float> Position;
        Vec2<float> Size;

        static bool Intersects(const Rect& a, const Rect& b)
        {
            return (std::abs(a.Position.x - b.Position.x) * 2 < (a.Size.x + b.Size.x)) && (std::abs(a.Position.y - b.Position.y) * 2 < (a.Size.y + b.Size.y));
        }
    };
}


#endif