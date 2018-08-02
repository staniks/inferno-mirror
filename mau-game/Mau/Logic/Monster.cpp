#include "Mau/States/Gameplay/GameplayState.h"
#include "Monster.h"
#include "Mau/Math/Math.h"
#include "Player.h"
#include "Projectile.h"
#include "Projectiles/Projectiles.h"

namespace Mau
{
    Monster::Monster(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition, int32 pHealth,
                     float pRange, float pMovementSpeed, const std::vector<std::vector<std::string>>& pAnimations)
        :
        Entity(pGameplayState, pLevel, EntityType::Monster, pPosition, {0.5f, 0.5f}, true, false),
        mHealth(pHealth),
        mRange(pRange),
        mMovementSpeed(pMovementSpeed)

    {
        for (auto& animation : pAnimations)
        {
            mAnimations.push_back(Animation{});
            for (auto& animationName : animation)
            {
                mAnimations.back().Frames.push_back(pGameplayState.GetEngine().TextureCache.GetResource(animationName));
            }
        }
    }

    void Monster::FixedUpdate(float pFixedDeltaTime)
    {
        Entity::FixedUpdate(pFixedDeltaTime);

        if (mDead)
        {
            if(mCurrentAnimation != AnimationIndex::Die)
            {
                mAnimationProgress = 0.0f;
            }
            mCurrentAnimation = AnimationIndex::Die;
            return;
        }

        auto delta = mLevel.GetPlayer()->GetPosition() - GetPosition();

        if(mAware)
        {
            if (delta.Length() > mRange)
            {
                if(mCurrentAnimation != AnimationIndex::Attack)
                {
                    SetVelocity(delta.Normalized() * pFixedDeltaTime * mMovementSpeed);/*
                    if (mCurrentAnimation == AnimationIndex::Attack)
                    {
                        mAnimationProgress = 0.0f;
                    }*/
                    mCurrentAnimation = AnimationIndex::Walk;
                }
            }
            else
            {
                if (mCurrentAnimation == AnimationIndex::Walk)
                {
                    mAnimationProgress = 0.0f;
                }
                mCurrentAnimation = AnimationIndex::Attack;
                if(mAnimationProgress == 0)
                {
                    OnFire(delta.Normalized());
                }
            }
        }      
        else
        {
            const auto hitInfo = mLevel.RaycastWall(GetPosition(), delta.Normalized());
            if((hitInfo.HitPosition - GetPosition()).Length() > delta.Length())
            {
                mAware = true;
            }
        }
    }

    void Monster::Update(float pDeltaTime)
    {
        Entity::Update(pDeltaTime);

        mAnimationProgress += pDeltaTime * mAnimationSpeed;
        if (mAnimationProgress >= GetCurrentAnimationLength())
        {
            if(!mDead)
            {
                mAnimationProgress = 0;            
                if (mCurrentAnimation == AnimationIndex::Attack)
                {
                    mCurrentAnimation = AnimationIndex::Walk;                    
                }
            }
            else
            {
                mAnimationProgress = GetCurrentAnimationLength() - 1;
            }
        }
    }

    Texture* Monster::GetCurrentTexture() const
    {
        size_t currentFrame = mAnimationProgress;
        currentFrame = Clamp(currentFrame, size_t(0), GetCurrentAnimationLength() - 1);
        return mAnimations[static_cast<size_t>(mCurrentAnimation)].Frames[currentFrame].get();
    }

    void Monster::OnEntityCollision(Entity* pEntity)
    {
    }

    void Monster::TakeDamage(float pDamage)
    {
        mHealth -= pDamage;
        if(mHealth <= 0)
        {
            mHealth = 0;
            mDead = true;
            mBlocking = false;
        }
    }

    bool Monster::IsDead() const
    {
        return mDead;
    }

    size_t Monster::GetCurrentAnimationLength() const
    {
        return mAnimations[static_cast<size_t>(mCurrentAnimation)].Frames.size();
    }
}
