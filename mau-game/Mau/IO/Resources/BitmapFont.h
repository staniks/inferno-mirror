#ifndef MAU_BITMAP_FONT_H
#define MAU_BITMAP_FONT_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/IO/Resources/LexData.h"
#include "Mau/IO/Resources/Texture.h"

namespace Mau
{
    /* A monospace font in ASCII order. */
    class BitmapFont : public LexData
    {
    public:
        explicit BitmapFont(const std::string& pPath);        

        const Texture* GetTexture() const;

    private:
        const Texture mTexture;

    public:
        const Vec2i CharacterCount;
        const Vec2i CharacterSize;
    };
}


#endif
