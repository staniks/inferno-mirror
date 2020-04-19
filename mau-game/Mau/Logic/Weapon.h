#ifndef MAU_WEAPON_H
#define MAU_WEAPON_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/IO/Resources/Texture.h"
#include "Mau/States/Gameplay/GameplayState.h"

namespace Mau
{
    class Engine;
    class Level;
    class Player;

    enum class AmmoType
    {
        Toilet,
        Plasma,
        Rocket,
        Count //enum length lol
    };

    class Weapon
    {
    public:
        explicit Weapon(std::shared_ptr<Texture> pTexture, std::shared_ptr<Texture> pCrosshairTexture, int32 pStartingAmmo, float pRecoilSpeed = 0.05f, float pRecoverySpeed = 0.0015f);

        Texture* GetTexture();
        int32 GetAmmo() const;

        void AddAmmo(int32 pAmount);

        const float RecoilSpeed;
        const float RecoverySpeed;

        virtual void OnFire(GameplayState& pGameplayState, Level& pLevel, Vec2f pPosition, Vec2f pDirection, Vec2f pRight) = 0;
        virtual AmmoType GetAmmoType() = 0; //for binding weapon to ammo pickups

        std::shared_ptr<Texture> CrosshairTexture;

    protected:
        std::shared_ptr<Texture> mTexture;

        int32 mAmmo{0};
    };

    class WeaponToilet : public Weapon
    {
    public:
        explicit WeaponToilet(Engine& pEngine);

        void OnFire(GameplayState& pGameplayState, Level& pLevel, Vec2f pPosition, Vec2f pDirection, Vec2f pRight) override;
        AmmoType GetAmmoType() override;
    };

    class WeaponPlasma : public Weapon
    {
    public:
        explicit WeaponPlasma(Engine& pEngine);

        void OnFire(GameplayState& pGameplayState, Level& pLevel, Vec2f pPosition, Vec2f pDirection, Vec2f pRight) override;
        AmmoType GetAmmoType() override;
    };

    class WeaponRocket : public Weapon
    {
    public:
        explicit WeaponRocket(Engine& pEngine);

        void OnFire(GameplayState& pGameplayState, Level& pLevel, Vec2f pPosition, Vec2f pDirection, Vec2f pRight) override;
        AmmoType GetAmmoType() override;
    };
}

#endif
