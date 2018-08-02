#ifndef MAU_RENDER_DEVICE_H
#define MAU_RENDER_DEVICE_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include <memory>
#include <SDL.h>

#include "Mau/Base/Types.h"
#include "Mau/IO/Resources/Texture.h"
#include "Mau/IO/Resources/BitmapFont.h"
#include "Mau/Math/Color.h"

#define FONT_CHARACTERS_X 16
#define FONT_CHARACTERS_Y 16

namespace Mau
{
    class RenderDevice
    {
    public:
        class Lock
        {
            friend class RenderDevice;
        public:
            explicit Lock(RenderDevice* pRenderDevice);
            ~Lock();
        private:
            RenderDevice* mRenderDevice;
        };

        explicit RenderDevice(SDL_Renderer* pRenderer, const int32 pWidth, const int32 pHeight);

        inline void RenderPixel(const Vec2i& pCoordinates, const Color pColor) const;
        inline void RenderPixelAlphaBlend(const Vec2i& pCoordinates, const Color pColor) const;

        void RenderTexture(const Texture* pTexture, const Vec2i& pCoordinates) const;
        void RenderTexturePart(const Texture* pTexture, const Vec2i& pCoordinates, const Vec2i& pPartCoordinates,
                               const Vec2i& pPartSize) const;
        void RenderFill(const Color pColor) const;
        void RenderRect(const Vec2i& pCoordinates, const Vec2i& pSize, const Color pColor) const;

        void RenderCharacter(const BitmapFont* pBitmapFont, const Vec2i& pCoordinates, const char pCharacter) const;
        void RenderString(const BitmapFont* pBitmapFont, const Vec2i& pCoordinates, const std::string& pString) const;

        SDL_Texture* GetTexture() const;

        inline Color GetPixel(const Vec2i& pCoordinates) const;

    public:
        const int32 Width;
        const int32 Height;

    private:
        std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> mRenderTarget;
        Color* mPixels; //set when texture is locked
    };

    inline Color RenderDevice::GetPixel(const Vec2i& pCoordinates) const
    {
        return mPixels[pCoordinates.y * Width + pCoordinates.x];
    }

    inline void RenderDevice::RenderPixel(const Vec2i& pCoordinates, const Color pColor) const
    {
        mPixels[pCoordinates.y * Width + pCoordinates.x] = pColor;
    }

    inline void RenderDevice::RenderPixelAlphaBlend(const Vec2i& pCoordinates, const Color pColor) const
    {
        const Color pSrcColor = pColor;
        const Color pDstColor = GetPixel(pCoordinates);

        RenderPixel(pCoordinates, Color::AlphaBlend(pSrcColor, pDstColor));
    }
}

#endif
