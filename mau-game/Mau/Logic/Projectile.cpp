#include "Mau/States/Gameplay/GameplayState.h"
#include "Monster.h"
#include "Projectile.h"
#include "Player.h"

namespace Mau
{
    Projectile::Projectile(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition, Mau::Vec2f pVelocity,
                           Entity* pOwner, std::shared_ptr<Texture> pTexture)
        :
        Entity(pGameplayState, pLevel, EntityType::Projectile, pPosition, Vec2f{0.1f, 0.1f}, false, true),
        mVelocity(pVelocity),
        mOwner(pOwner),
        mTexture(pTexture)
    {
    }

    void Projectile::FixedUpdate(float pFixedDeltaTime)
    {
        Entity::FixedUpdate(pFixedDeltaTime);

        SetVelocity(mVelocity);
    }

    Texture* Projectile::GetCurrentTexture() const
    {
        return mTexture.get();
    }

    void Projectile::OnEntityCollision(Entity* pEntity)
    {
        if (this->mOwner == mLevel.GetPlayer())
        {
            if (pEntity->GetType() == EntityType::Monster)
            {
                Monster* monster = dynamic_cast<Monster*>(pEntity);
                if (!monster->IsDead())
                {
                    monster->TakeDamage(Damage);
                    OnWallCollision();
                }
            }
        }
        else
        {
            if (pEntity->GetType() == EntityType::Player)
            {
                Player* player = dynamic_cast<Player*>(pEntity);
                player->AddHealth(-Damage);
                mGameplayState.FlashScreen({ 255, 0, 0, 64 });
                OnWallCollision();
            }
        }
    }

    void Projectile::OnWallCollision()
    {
        //SetPosition is potentially dangerous here
        mPosition = GetPosition() - mVelocity * mGameplayState.GetEngine().FixedTimestepMiliseconds;
        mLevel.Spawn(CreateDestructionParticle()); //todo: add OnDestroy method and put this there instead?
        Destroy();
    }
}
