#ifndef MAU_MONSTER_H
#define MAU_MONSTER_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Logic/Entity.h"

namespace Mau
{
    class Monster : public Entity
    {
    public:
        enum class AnimationIndex
        {
            Walk,
            Attack,
            Die
        };

        struct Animation
        {
            std::vector<std::shared_ptr<Texture>> Frames;
        };

        Monster(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition, int32 pHealth, float pRange, float pMovementSpeed,
                const std::vector<std::vector<std::string>>& pAnimations);

        void FixedUpdate(float pFixedDeltaTime) override;
        void Update(float pDeltaTime) override;

        Texture* GetCurrentTexture() const override;
        void OnEntityCollision(Entity* pEntity) override;

        void TakeDamage(float pDamage);

        bool IsDead() const;

        virtual void OnFire(const Vec2f& pDirection) = 0;

    private:
        size_t GetCurrentAnimationLength() const;
        int32 mHealth;
        float mRange;
        float mMovementSpeed;

        std::vector<Animation> mAnimations;
        AnimationIndex mCurrentAnimation{AnimationIndex::Walk};

        float mAnimationProgress{ 0 };
        const float mAnimationSpeed{ 0.025f };        

        bool mAware{ false };
        bool mDead{ false };
    };
}

#endif
