#include "Mau/Base/State.h"

namespace Mau
{
    State::State(Engine& pEngine)
        :
        mEngine(pEngine)
    {
    }

    Engine& State::GetEngine() const
    {
        return mEngine;
    }
}
