#ifndef MAU_PARTICLE_H
#define MAU_PARTICLE_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Logic/Entity.h"

namespace Mau
{
    class Particle : public Entity
    {
    public:
        Particle(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition, std::vector<std::shared_ptr<Texture>> pAnimationFrames, float pVerticalOffset, float pAnimationSpeed = 0.001f);

        void Update(float pDeltaTime) override;

        Texture* GetCurrentTexture() const override;
        void OnEntityCollision(Entity* pEntity) override;

    private:
        const float mAnimationSpeed;
        std::vector<std::shared_ptr<Texture>> mAnimationFrames;

        float mAnimationProgress{ 0 };
    };
}

#endif
