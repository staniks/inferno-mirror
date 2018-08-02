#ifndef MAU_PICKUP_HEALTH_H
#define MAU_PICKUP_HEALTH_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Logic/Pickup.h"

namespace Mau
{
    class PickupHealth : public Pickup
    {
    public:
        PickupHealth(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition);

        void OnPlayerCollision() override;
    };

    class PickupArmor : public Pickup
    {
    public:
        PickupArmor(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition);

        void OnPlayerCollision() override;
    };
}

#endif
