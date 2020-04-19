#ifndef MAU_SDL_H
#define MAU_SDL_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

namespace Mau
{
    class SDLSystemMain
    {
    public:
        SDLSystemMain();
        ~SDLSystemMain();
    };    

    class SDLSystemImage
    {
    public:
        SDLSystemImage();
        ~SDLSystemImage();
    };

    class SDLSystemMixer
    {
    public:
        SDLSystemMixer();
        ~SDLSystemMixer();
    };
}

#endif
