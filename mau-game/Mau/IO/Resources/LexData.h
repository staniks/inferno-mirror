#ifndef MAU_LEXDATA_H
#define MAU_LEXDATA_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Base/Types.h"
#include "Mau/IO/Resource.h"
#include "Mau/IO/Resources/TextData.h"

namespace Mau
{
    /* Lexical analyzer. Splits text into lexems with space as delimiter. */
    class LexData : public Resource
    {
    public:
        explicit LexData(const std::string& pPath);

        const std::vector<std::string>& GetLexems() const;
        std::vector<std::string>::iterator GetIterator();

        int32 GetInt(size_t pIndex) const;
        std::string GetString(size_t pIndex) const;

    private:      

        std::vector<std::string> mLexems;
    };
}


#endif
