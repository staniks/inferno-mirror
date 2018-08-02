#ifndef MAU_LOG_H
#define MAU_LOG_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include <fstream>
#include <string>

namespace Mau
{
    class Log
    {
    public:
        static void Write(const std::string& pEntry);

    private:
        static std::ofstream mStream;
    };

#define MAU_LOG(message) (Log::Write(message))
}

#endif
