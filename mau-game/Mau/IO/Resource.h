#ifndef MAU_RESOURCE_H
#define MAU_RESOURCE_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include <string>
#include <vector>

namespace Mau
{
    class Resource
    {
    public:
        explicit Resource(const std::string& pPath);

        // todo: add other constructors (rule of 5)

        virtual ~Resource();

    protected:
        const std::string mPath;
    };
}


#endif
