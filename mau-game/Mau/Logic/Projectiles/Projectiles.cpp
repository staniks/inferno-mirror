#include "Mau/States/Gameplay/GameplayState.h"
#include "Projectiles.h"
#include "Mau/Logic/Player.h"

namespace Mau
{
    /*
     * TOILET PROJECTILE
     */
    ProjectileToilet::ProjectileToilet(GameplayState& pGameplayState, Level& pLevel, const Mau::Vec2f& pPosition,
                                       const Mau::Vec2f& pVelocity, Entity* pOwner)
        : Projectile(pGameplayState, pLevel, pPosition, pVelocity, pOwner,
                     pGameplayState.GetEngine().TextureCache.GetResource("toilet_projectile.png"))
    {
        Damage = 10;
    }

    std::unique_ptr<Particle> ProjectileToilet::CreateDestructionParticle()
    {
        return std::make_unique<Particle>(mGameplayState, mLevel, GetPosition(), std::vector<std::shared_ptr<Texture>>{
            mGameplayState.GetEngine().TextureCache.GetResource("toilet_particle_1.png"),
            mGameplayState.GetEngine().TextureCache.GetResource("toilet_particle_2.png")
        }, 0, 0.01f);
    }

    /*
    * PLASMA PROJECTILE
    */
    ProjectilePlasma::ProjectilePlasma(GameplayState& pGameplayState, Level& pLevel, const Mau::Vec2f& pPosition,
                                       const Mau::Vec2f& pVelocity, Entity* pOwner)
        : Projectile(pGameplayState, pLevel, pPosition, pVelocity, pOwner,
                     pGameplayState.GetEngine().TextureCache.GetResource("plasma_projectile.png"))
    {
        Damage = 15;
    }

    std::unique_ptr<Particle> ProjectilePlasma::CreateDestructionParticle()
    {
        return std::make_unique<Particle>(mGameplayState, mLevel, GetPosition(), std::vector<std::shared_ptr<Texture>>{
            mGameplayState.GetEngine().TextureCache.GetResource("plasma_particle_1.png"),
            mGameplayState.GetEngine().TextureCache.GetResource("plasma_particle_2.png")
        }, 0, 0.01f);
    }

    /*
    * ROCKET PROJECTILE
    */
    ProjectileRocket::ProjectileRocket(GameplayState& pGameplayState, Level& pLevel, const Mau::Vec2f& pPosition,
                                       const Mau::Vec2f& pVelocity, Entity* pOwner)
        : Projectile(pGameplayState, pLevel, pPosition, pVelocity, pOwner,
                     pGameplayState.GetEngine().TextureCache.GetResource("rocket_projectile.png"))
    {
        Damage = 50;
    }

    std::unique_ptr<Particle> ProjectileRocket::CreateDestructionParticle()
    {
        return std::make_unique<Particle>(mGameplayState, mLevel, GetPosition(), std::vector<std::shared_ptr<Texture>>{
            mGameplayState.GetEngine().TextureCache.GetResource("particle_rocket_1.png"),
            mGameplayState.GetEngine().TextureCache.GetResource("particle_rocket_2.png"),
            mGameplayState.GetEngine().TextureCache.GetResource("particle_rocket_3.png"),
            mGameplayState.GetEngine().TextureCache.GetResource("particle_rocket_4.png"),
            mGameplayState.GetEngine().TextureCache.GetResource("particle_rocket_5.png"),
            mGameplayState.GetEngine().TextureCache.GetResource("particle_rocket_6.png"),
            mGameplayState.GetEngine().TextureCache.GetResource("particle_rocket_7.png"),
            mGameplayState.GetEngine().TextureCache.GetResource("particle_rocket_8.png"),
        }, 6, 0.01f);
    }

    /*
    * ENEMY PLASMA PROJECTILE
    */
    ProjectileEnemyPlasma::ProjectileEnemyPlasma(GameplayState& pGameplayState, Level& pLevel,
                                                 const Mau::Vec2f& pPosition,
                                                 const Mau::Vec2f& pVelocity, Entity* pOwner)
        : Projectile(pGameplayState, pLevel, pPosition, pVelocity, pOwner,
                     pGameplayState.GetEngine().TextureCache.GetResource("plasma_enemy.png"))
    {
        Damage = 5;
    }

    std::unique_ptr<Particle> ProjectileEnemyPlasma::CreateDestructionParticle()
    {
        return std::make_unique<Particle>(mGameplayState, mLevel, GetPosition(), std::vector<std::shared_ptr<Texture>>{
            mGameplayState.GetEngine().TextureCache.GetResource("enemy_particle_1.png"),
            mGameplayState.GetEngine().TextureCache.GetResource("enemy_particle_2.png")
        }, 0, 0.01f);
    }

    /*
    * ENEMY TRACKING PROJECTILE
    */
    ProjectileEnemyTracking::ProjectileEnemyTracking(GameplayState& pGameplayState, Level& pLevel,
                                                     const Mau::Vec2f& pPosition,
                                                     const Mau::Vec2f& pVelocity, Entity* pOwner)
        : Projectile(pGameplayState, pLevel, pPosition, pVelocity, pOwner,
                     pGameplayState.GetEngine().TextureCache.GetResource("tracking_projectile.png"))
    {
        Damage = 20;
    }

    void ProjectileEnemyTracking::FixedUpdate(float pFixedDeltaTime)
    {
        Projectile::FixedUpdate(pFixedDeltaTime);

        SetVelocity((mLevel.GetPlayer()->GetPosition() - GetPosition()).Normalized() * mVelocity.Length());

        mLifetime -= pFixedDeltaTime / 1000.0f;
        if(mLifetime <= 0)
        {
            OnWallCollision();
        }
    }

    std::unique_ptr<Particle> ProjectileEnemyTracking::CreateDestructionParticle()
    {
        return std::make_unique<Particle>(mGameplayState, mLevel, GetPosition(), std::vector<std::shared_ptr<Texture>>{
            mGameplayState.GetEngine().TextureCache.GetResource("tracking_particle_1.png"),
            mGameplayState.GetEngine().TextureCache.GetResource("tracking_particle_2.png")
        }, 0, 0.01f);
    }

    /*
    * ENEMY SHOTGUN PROJECTILE
    */
    ProjectileEnemyShotgun::ProjectileEnemyShotgun(GameplayState& pGameplayState, Level& pLevel,
        const Mau::Vec2f& pPosition,
        const Mau::Vec2f& pVelocity, Entity* pOwner)
        : Projectile(pGameplayState, pLevel, pPosition, pVelocity, pOwner,
            pGameplayState.GetEngine().TextureCache.GetResource("shotgun_enemy.png"))
    {
        Damage = 5;
    }

    std::unique_ptr<Particle> ProjectileEnemyShotgun::CreateDestructionParticle()
    {
        return std::make_unique<Particle>(mGameplayState, mLevel, GetPosition(), std::vector<std::shared_ptr<Texture>>{
            mGameplayState.GetEngine().TextureCache.GetResource("enemy_particle_1.png"),
                mGameplayState.GetEngine().TextureCache.GetResource("enemy_particle_2.png")
        }, 0, 0.01f);
    }
}
