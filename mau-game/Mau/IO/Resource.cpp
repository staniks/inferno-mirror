#include "Mau/Base/Types.h"
#include "Mau/IO/Resource.h"
#include "Mau/IO/Log.h"

namespace Mau
{
    Resource::Resource(const std::string& pPath)
        :
        mPath(pPath)
    {
        MAU_LOG("Loading resource " + mPath);
    }
    Resource::~Resource()
    {
        MAU_LOG("Freeing resource " + mPath);
    }
}
