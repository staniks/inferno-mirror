#include "Mau/IO/Resources/Sound.h"

namespace Mau
{
    Sound::Sound(const std::string& pPath)
        :
        Resource(pPath),
        mChunk{ Mix_LoadWAV(pPath.c_str()), Mix_FreeChunk}
    {

    }

    void Sound::Play()
    {
        Mix_PlayChannel(-1, mChunk.get(), 0);
    }
}
