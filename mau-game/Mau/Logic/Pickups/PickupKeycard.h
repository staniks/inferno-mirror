#ifndef MAU_PICKUP_KEYCARD_H
#define MAU_PICKUP_KEYCARD_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Logic/Pickup.h"

namespace Mau
{
    class PickupKeycardRed : public Pickup
    {
    public:
        PickupKeycardRed(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition);

        void OnPlayerCollision() override;
    };

    class PickupKeycardBlue : public Pickup
    {
    public:
        PickupKeycardBlue(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition);

        void OnPlayerCollision() override;
    };

    class PickupKeycardYellow : public Pickup
    {
    public:
        PickupKeycardYellow(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition);

        void OnPlayerCollision() override;
    };
}

#endif
