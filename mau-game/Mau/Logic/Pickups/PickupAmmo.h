#ifndef MAU_PICKUP_AMMO_H
#define MAU_PICKUP_AMMO_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Logic/Pickup.h"

namespace Mau
{
    class PickupAmmoToilet : public Pickup
    {
    public:
        PickupAmmoToilet(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition);

        void OnPlayerCollision() override;
    };

    class PickupAmmoPlasma : public Pickup
    {
    public:
        PickupAmmoPlasma(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition);

        void OnPlayerCollision() override;
    };

    class PickupAmmoRocket : public Pickup
    {
    public:
        PickupAmmoRocket(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition);

        void OnPlayerCollision() override;
    };
}

#endif
