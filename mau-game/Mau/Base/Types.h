#ifndef MAU_TYPES_H
#define MAU_TYPES_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include <stdexcept>

#include "Mau/Math/Vec2.h"

namespace Mau
{
    typedef signed char        int8;
    typedef signed short int   int16;
    typedef signed int         int32;
    typedef signed long long   int64;
    typedef unsigned char      uint8;
    typedef unsigned short int uint16;
    typedef unsigned int       uint32;
    typedef unsigned long long uint64;
    typedef unsigned char      byte;

    typedef std::runtime_error Exception;

    typedef Vec2<int32> Vec2i;

    typedef Vec2<float> Vec2f;
}

#endif
