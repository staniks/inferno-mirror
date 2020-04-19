#ifndef MAU_TEXTDATA_H
#define MAU_TEXTDATA_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/IO/Resource.h"

namespace Mau
{
    class TextData : public Resource
    {
    public:
        explicit TextData(const std::string& pPath);

        const std::string& GetText() const;

    private:
        std::string mText;
    };
}


#endif
