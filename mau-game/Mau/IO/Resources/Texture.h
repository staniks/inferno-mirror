#ifndef MAU_TEXTURE_H
#define MAU_TEXTURE_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include <string>
#include <memory>
#include <SDL.h>

#include "Mau/Base/Types.h"
#include "Mau/IO/Resource.h"
#include "Mau/Math/Color.h"

namespace Mau
{
    class Texture : public Resource
    {
    public:
        explicit Texture(const std::string& pPath);

        inline int32 GetWidth() const;
        inline int32 GetHeight() const;

        inline Color GetPixelColor(const Vec2i pCoordinates) const;

    private:
        std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> mSurface;
    };

    inline int32 Texture::GetWidth() const
    {
        return mSurface->w;
    }

    inline int32 Texture::GetHeight() const
    {
        return mSurface->h;
    }

    inline Color Texture::GetPixelColor(const Vec2i pCoordinates) const
    {
        return static_cast<Color*>(mSurface->pixels)[pCoordinates.y * mSurface->w + pCoordinates.x];
    }
}


#endif
