#include "Particle.h"
#include "Mau/IO/Log.h"
#include "Mau/Math/Math.h"

namespace Mau
{
    Particle::Particle(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition, std::vector<std::shared_ptr<Texture>> pAnimationFrames, float pVerticalOffset, float pAnimationSpeed)
        :
        Entity(pGameplayState, pLevel, EntityType::Particle, pPosition, Vec2f{ 0.5f, 0.5f }, false, true),
        mAnimationSpeed(pAnimationSpeed),
        mAnimationFrames(pAnimationFrames)        
    {
        VerticalOffset = pVerticalOffset;
    }

    void Particle::Update(float pDeltaTime)
    {
        Entity::Update(pDeltaTime);

        mAnimationProgress += pDeltaTime * mAnimationSpeed;
        if(mAnimationProgress >= mAnimationFrames.size())
        {
            Destroy();
        }
    }

    Texture* Particle::GetCurrentTexture() const
    {
        const size_t currentFrame = Clamp(static_cast<size_t>(mAnimationProgress), size_t(0), mAnimationFrames.size() - 1);
        return mAnimationFrames[currentFrame].get();
    }

    void Particle::OnEntityCollision(Entity* pEntity)
    {
        
    }
}
