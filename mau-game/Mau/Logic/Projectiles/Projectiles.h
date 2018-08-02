#ifndef MAU_PROJECTILES_H
#define MAU_PROJECTILES_H

#include "Mau/Logic/Projectile.h"

namespace Mau
{
    class ProjectileToilet : public Projectile
    {
    public:
        ProjectileToilet(GameplayState& pGameplayState, Level& pLevel, const Mau::Vec2f& pPosition,
                         const Mau::Vec2f& pVelocity, Entity* pOwner);

        std::unique_ptr<Particle> CreateDestructionParticle() override;
    };

    class ProjectilePlasma : public Projectile
    {
    public:
        ProjectilePlasma(GameplayState& pGameplayState, Level& pLevel, const Mau::Vec2f& pPosition,
                         const Mau::Vec2f& pVelocity, Entity* pOwner);

        std::unique_ptr<Particle> CreateDestructionParticle() override;
    };

    class ProjectileRocket : public Projectile
    {
    public:
        ProjectileRocket(GameplayState& pGameplayState, Level& pLevel, const Mau::Vec2f& pPosition,
                         const Mau::Vec2f& pVelocity, Entity* pOwner);

        std::unique_ptr<Particle> CreateDestructionParticle() override;
    };

    class ProjectileEnemyPlasma : public Projectile
    {
    public:
        ProjectileEnemyPlasma(GameplayState& pGameplayState, Level& pLevel, const Mau::Vec2f& pPosition,
            const Mau::Vec2f& pVelocity, Entity* pOwner);

        std::unique_ptr<Particle> CreateDestructionParticle() override;
    };

    class ProjectileEnemyShotgun : public Projectile
    {
    public:
        ProjectileEnemyShotgun(GameplayState& pGameplayState, Level& pLevel, const Mau::Vec2f& pPosition,
            const Mau::Vec2f& pVelocity, Entity* pOwner);

        std::unique_ptr<Particle> CreateDestructionParticle() override;
    };

    class ProjectileEnemyTracking : public Projectile
    {
    public:
        ProjectileEnemyTracking(GameplayState& pGameplayState, Level& pLevel, const Mau::Vec2f& pPosition,
            const Mau::Vec2f& pVelocity, Entity* pOwner);

        void FixedUpdate(float pFixedDeltaTime) override;

        std::unique_ptr<Particle> CreateDestructionParticle() override;

    private:
        float mLifetime{ 2.5 };
    };
}

#endif
