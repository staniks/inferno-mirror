#ifndef MAU_PICKUP_RELIC_H
#define MAU_PICKUP_RELIC_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Logic/Pickup.h"

namespace Mau
{
    class PickupRelic : public Pickup
    {
    public:
        PickupRelic(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition, const std::string& pName, const std::string& pDialogueId);

        void OnPlayerCollision() override;
    private:
        std::string mName;
        std::string mDialogueId;
    };
}

#endif
