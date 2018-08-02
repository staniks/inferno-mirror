#include "Pickup.h"
#include "Mau/IO/Log.h"

namespace Mau
{
    Pickup::Pickup(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition, std::shared_ptr<Texture> pTexture)
        :
        Entity(pGameplayState, pLevel, EntityType::Pickup, pPosition, Vec2f{0.5f, 0.5f}, false, true),
        mTexture(pTexture)
    {
    }

    Texture* Pickup::GetCurrentTexture() const
    {
        return mTexture.get();
    }

    void Pickup::OnEntityCollision(Entity* pEntity)
    {
        if(pEntity->GetType() == EntityType::Player)
        {
            OnPlayerCollision();
        }
    }
}
