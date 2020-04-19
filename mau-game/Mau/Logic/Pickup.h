#ifndef MAU_PICKUP_H
#define MAU_PICKUP_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Logic/Entity.h"

namespace Mau
{
    class Pickup : public Entity
    {
    public:
        Pickup(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition, std::shared_ptr<Texture> pTexture);

        Texture* GetCurrentTexture() const override;
        void OnEntityCollision(Entity* pEntity) override;

        virtual void OnPlayerCollision() = 0;

    private:
        std::shared_ptr<Texture> mTexture;
    };
}

#endif
