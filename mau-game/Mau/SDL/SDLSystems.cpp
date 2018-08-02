#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Mau/Base/Types.h"
#include "Mau/IO/Log.h"
#include "Mau/SDL/SDLSystems.h"

namespace Mau
{
    // /////////////////
    // SDL library
    // /////////////////
    SDLSystemMain::SDLSystemMain()
    {
        MAU_LOG("Initializing SDL...");
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            throw Exception(SDL_GetError());
        }
    }

    SDLSystemMain::~SDLSystemMain()
    {
        MAU_LOG("Quitting SDL...");
        SDL_Quit();
    }

    // /////////////////
    // SDL_image library
    // /////////////////
    SDLSystemImage::SDLSystemImage()
    {
        MAU_LOG("Initializing SDL image...");
        if (IMG_Init(IMG_INIT_PNG) == 0)
        {
            throw Exception(IMG_GetError());
        }
    }

    SDLSystemImage::~SDLSystemImage()
    {
        MAU_LOG("Quitting SDL image...");
        IMG_Quit();
    }

    // /////////////////
    // SDL_mixer library
    // /////////////////
    SDLSystemMixer::SDLSystemMixer()
    {
        MAU_LOG("Initializing SDL mixer...");
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            throw Exception(IMG_GetError());
        }
    }

    SDLSystemMixer::~SDLSystemMixer()
    {
        MAU_LOG("Quitting SDL mixer...");
        Mix_CloseAudio();
    }
}
