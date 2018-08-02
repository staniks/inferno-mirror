#include <iostream>

#include "Mau/IO/Log.h"

namespace Mau
{
    std::ofstream Log::mStream{ "log.txt" };

    void Log::Write(const std::string& pEntry)
    {
        mStream << pEntry << '\n';
        std::cout << pEntry << '\n';
    }
}
