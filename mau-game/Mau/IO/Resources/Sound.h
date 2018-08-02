#ifndef MAU_SOUND_H
#define MAU_SOUND_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include <memory>
#include <SDL_mixer.h>

#include "Mau/IO/Resource.h"

namespace Mau
{
    class Sound : public Resource
    {
    public:
        explicit Sound(const std::string& pPath);

        void Play();

    private:
        std::unique_ptr<Mix_Chunk, void(*)(Mix_Chunk*)> mChunk;
    };
}


#endif
