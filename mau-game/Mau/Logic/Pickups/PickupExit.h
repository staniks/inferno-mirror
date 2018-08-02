#ifndef MAU_PICKUP_EXIT_H
#define MAU_PICKUP_EXIT_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Logic/Pickup.h"

namespace Mau
{
    class PickupExit : public Pickup
    {
    public:
        PickupExit(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition);

        void OnPlayerCollision() override;
    };
}

#endif
