#include "BitmapFont.h"
#include "Mau/IO/ResourceCache.h"

namespace Mau
{
    BitmapFont::BitmapFont(const std::string& pPath)
        :
        LexData(pPath),
        mTexture(RESOURCE_DIRECTORY_PREFIX + GetString(2)), //todo: error prone, make it different
        CharacterCount(GetInt(0), GetInt(1)),
        CharacterSize(mTexture.GetWidth() / CharacterCount.x, mTexture.GetHeight() / CharacterCount.y)
    {
    }

    const Texture* BitmapFont::GetTexture() const
    {
        return &mTexture;
    }
}
