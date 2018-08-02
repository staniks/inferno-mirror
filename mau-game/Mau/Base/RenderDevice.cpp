#include <algorithm>

#include "Mau/Base/RenderDevice.h"

// These macros were interfering with use of std::max and std::min.
#undef max
#undef min

namespace Mau
{
    RenderDevice::Lock::Lock(RenderDevice* pRenderDevice)
        :
        mRenderDevice(pRenderDevice)
    {
        int pitch; //useless because we already know the pitch, but hey
        SDL_LockTexture(mRenderDevice->mRenderTarget.get(), nullptr, reinterpret_cast<void**>(&mRenderDevice->mPixels),
                        &pitch);
    }

    RenderDevice::Lock::~Lock()
    {
        SDL_UnlockTexture(mRenderDevice->mRenderTarget.get());
    }

    RenderDevice::RenderDevice(SDL_Renderer* pRenderer, const int32 pWidth, const int32 pHeight)
        :
        Width(pWidth),
        Height(pHeight),
        mRenderTarget(
            SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, pWidth, pHeight),
            SDL_DestroyTexture),
        mPixels(nullptr)
    {
    }

    SDL_Texture* RenderDevice::GetTexture() const
    {
        return mRenderTarget.get();
    }

    void RenderDevice::RenderTexture(const Texture* pTexture, const Vec2i& pCoordinates) const
    {
        Vec2i currentDeviceCoordinate = pCoordinates;

        for (auto x = 0; x < pTexture->GetWidth(); ++x, ++currentDeviceCoordinate.x)
        {
            currentDeviceCoordinate.y = pCoordinates.y;

            for (auto y = 0; y < pTexture->GetHeight(); ++y, ++currentDeviceCoordinate.y)
            {
                // TODO: ugly and slow, perform bounds check outside loops
                if (currentDeviceCoordinate.x < 0
                    || currentDeviceCoordinate.y < 0
                    || currentDeviceCoordinate.x >= Width
                    || currentDeviceCoordinate.y >= Height)
                {
                    continue;
                }

                RenderPixelAlphaBlend(currentDeviceCoordinate, pTexture->GetPixelColor({x, y}));
            }
        }
    }

    void RenderDevice::RenderTexturePart(const Texture* pTexture, const Vec2i& pCoordinates,
                                         const Vec2i& pPartCoordinates, const Vec2i& pPartSize) const
    {
        Vec2i currentDeviceCoordinate = pCoordinates;

        for (auto x = pPartCoordinates.x; x < pPartCoordinates.x + pPartSize.x; ++x, ++currentDeviceCoordinate.x)
        {
            currentDeviceCoordinate.y = pCoordinates.y;

            for (auto y = pPartCoordinates.y; y < pPartCoordinates.y + pPartSize.y; ++y, ++currentDeviceCoordinate.y)
            {
                // TODO: ugly and slow, perform bounds check outside loops
                if (currentDeviceCoordinate.x < 0
                    || currentDeviceCoordinate.y < 0
                    || currentDeviceCoordinate.x >= Width
                    || currentDeviceCoordinate.y >= Height)
                {
                    continue;
                }

                RenderPixelAlphaBlend(currentDeviceCoordinate, pTexture->GetPixelColor({x, y}));
            }
        }
    }

    void RenderDevice::RenderFill(const Color pColor) const
    {
        for (int y = 0; y < Height; ++y)
        {
            for (int x = 0; x < Width; ++x)
            {
                RenderPixelAlphaBlend({x, y}, pColor);
            }
        }
    }

    void RenderDevice::RenderRect(const Vec2i& pCoordinates, const Vec2i& pSize, const Color pColor) const
    {
        for (int y = pCoordinates.y; y < pCoordinates.y + pSize.y; ++y)
        {
            for (int x = pCoordinates.x; x < pCoordinates.x + pSize.x; ++x)
            {
                // TODO: ugly and slow, perform bounds check outside loops
                if (x < 0 || y < 0 || x >= Width || y >= Height)
                {
                    continue;
                }

                RenderPixelAlphaBlend({x, y}, pColor);
            }
        }
    }

    void RenderDevice::RenderCharacter(const BitmapFont* pBitmapFont, const Vec2i& pCoordinates,
                                       const char pCharacter) const
    {        
        //Note - assume the font sheet is arranged in ASCII order.

        const Vec2i characterPartSize{
            pBitmapFont->GetTexture()->GetWidth() / pBitmapFont->CharacterCount.x, pBitmapFont->GetTexture()->GetHeight() / pBitmapFont->CharacterCount.y
        };
        const Vec2i characterPartCoordinates
        {
            (pCharacter % pBitmapFont->CharacterCount.x) * characterPartSize.x,
            (pCharacter / pBitmapFont->CharacterCount.x) * characterPartSize.y
        };

        RenderTexturePart(pBitmapFont->GetTexture(), pCoordinates, characterPartCoordinates, characterPartSize);
    }

    void RenderDevice::RenderString(const BitmapFont* pBitmapFont, const Vec2i& pCoordinates,
                                    const std::string& pString) const
    {
        const int32 deltaX = pBitmapFont->GetTexture()->GetWidth() / pBitmapFont->CharacterCount.x;

        for (int32 i = 0; i < pString.length(); ++i)
        {
            RenderCharacter(pBitmapFont, pCoordinates + Vec2i{deltaX * i, 0}, pString[i]);
        }
    }
}
