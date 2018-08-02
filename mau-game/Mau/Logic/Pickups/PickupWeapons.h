#ifndef MAU_PICKUP_WEAPON_TOILET_H
#define MAU_PICKUP_WEAPON_TOILET_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Logic/Pickup.h"

namespace Mau
{
    class PickupWeaponToilet : public Pickup
    {
    public:
        PickupWeaponToilet(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition);

        void OnPlayerCollision() override;
    };

    class PickupWeaponPlasma : public Pickup
    {
    public:
        PickupWeaponPlasma(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition);

        void OnPlayerCollision() override;
    };

    class PickupWeaponRocket : public Pickup
    {
    public:
        PickupWeaponRocket(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition);

        void OnPlayerCollision() override;
    };

    
}

#endif
