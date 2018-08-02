#ifndef MAU_PROJECTILE_H
#define MAU_PROJECTILE_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Logic/Entity.h"
#include "Particle.h"

namespace Mau
{
    class Projectile : public Entity
    {
    public:
        Projectile(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition, Mau::Vec2f pVelocity,
                   Entity* pOwner, std::shared_ptr<Texture> pTexture);

        void FixedUpdate(float pFixedDeltaTime) override;

        Texture* GetCurrentTexture() const override;
        void OnEntityCollision(Entity* pEntity) override;
        void OnWallCollision() override;

        virtual std::unique_ptr<Particle> CreateDestructionParticle() = 0;

        float Damage{ 10 };

    protected:
        Vec2f mVelocity;
        Entity* mOwner;
    
        std::shared_ptr<Texture> mTexture;
    };
}

#endif
