#include <SDL_image.h>

#include "Mau/IO/Resources/Texture.h"

namespace Mau
{
    Texture::Texture(const std::string& pPath)
        :
        Resource(pPath),
        mSurface{ IMG_Load(pPath.c_str()), SDL_FreeSurface }
    {
        
    }
}
