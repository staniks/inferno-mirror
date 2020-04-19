#include "Weapon.h"
#include "Mau/Base/Engine.h"
#include "Projectile.h"
#include "Player.h"
#include "Projectiles/Projectiles.h"

namespace Mau
{
    Weapon::Weapon(std::shared_ptr<Texture> pTexture, std::shared_ptr<Texture> pCrosshairTexture, int32 pStartingAmmo, float pRecoilSpeed, float pRecoverySpeed)
        :
        mTexture(pTexture),
        CrosshairTexture(pCrosshairTexture),
        mAmmo(pStartingAmmo),
        RecoilSpeed(pRecoilSpeed),
        RecoverySpeed(pRecoverySpeed)
    {
    }

    Texture* Weapon::GetTexture()
    {
        return mTexture.get();
    }

    int32 Weapon::GetAmmo() const
    {
        return mAmmo;
    }

    void Weapon::AddAmmo(int32 pAmount)
    {
        mAmmo += pAmount;
    }

    WeaponToilet::WeaponToilet(Engine& pEngine)
        : Weapon(pEngine.TextureCache.GetResource("weapon_toilet.png"), pEngine.TextureCache.GetResource("crosshair_shotgun.png"), 8)
    {
    }

    void WeaponToilet::OnFire(GameplayState& pGameplayState, Level& pLevel, Vec2f pPosition, Vec2f pDirection, Vec2f pRight)
    {
        --mAmmo;
        for (int i = 0; i<3; ++i)
        {
            Vec2f velocity = pDirection * 0.0075f + pRight * (i - 1) * 0.00075f;
            velocity *= 2.0f;
            pLevel.Spawn(std::make_unique<ProjectileToilet>(pGameplayState, pLevel, pPosition, velocity, pLevel.GetPlayer()));
        }
    }

    AmmoType WeaponToilet::GetAmmoType()
    {
        return AmmoType::Toilet;
    }

    WeaponPlasma::WeaponPlasma(Engine& pEngine)
        : Weapon(pEngine.TextureCache.GetResource("weapon_plasma.png"), pEngine.TextureCache.GetResource("crosshair_plasma.png"), 16, 0.1f, 0.005f)
    {
    }

    void WeaponPlasma::OnFire(GameplayState& pGameplayState, Level& pLevel, Vec2f pPosition, Vec2f pDirection, Vec2f pRight)
    {
        --mAmmo;
        Vec2f velocity = pDirection * 0.015f;            
        pLevel.Spawn(std::make_unique<ProjectilePlasma>(pGameplayState, pLevel, pPosition, velocity, pLevel.GetPlayer()));        
    }

    AmmoType WeaponPlasma::GetAmmoType()
    {
        return AmmoType::Plasma;
    }

    WeaponRocket::WeaponRocket(Engine& pEngine)
        : Weapon(pEngine.TextureCache.GetResource("weapon_rocket.png"), pEngine.TextureCache.GetResource("crosshair_rocket.png"), 4)
    {
    }

    void WeaponRocket::OnFire(GameplayState& pGameplayState, Level& pLevel, Vec2f pPosition, Vec2f pDirection, Vec2f pRight)
    {
        --mAmmo;
        Vec2f velocity = pDirection * 0.015f;
        pLevel.Spawn(std::make_unique<ProjectileRocket>(pGameplayState, pLevel, pPosition, velocity, pLevel.GetPlayer()));
    }

    AmmoType WeaponRocket::GetAmmoType()
    {
        return AmmoType::Rocket;
    }
}
