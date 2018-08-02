#include <iostream>
#include <fstream>
#include <sstream>

#include "Mau/Base/Types.h"
#include "Mau/IO/Resources/TextData.h"

namespace Mau
{
    TextData::TextData(const std::string& pPath)
        :
        Resource(pPath)
    {
        /* We're dealing with small files, so we can get away with 
         * loading everything into string rather than encapsulating 
         * the stream. */

        std::ifstream stream(pPath);
        if(!stream)
        {
            throw Mau::Exception("Unable to open " + pPath);
        }
        
        std::stringstream buffer;
        buffer << stream.rdbuf();

        mText = buffer.str();
    }

    const std::string& TextData::GetText() const
    {
        return mText;
    }
}
