#ifndef MAU_PLAYER_H
#define MAU_PLAYER_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Logic/Entity.h"
#include "Mau/Logic/Weapon.h"
#include "Mau/Math/Math.h"

namespace Mau
{
    enum class WeaponSwitchState
    {
        Holstering,
        Arming,
        None
    };

    enum class WeaponFiringState
    {
        Recoiling,
        Recovering,
        Ready
    };

    class Player : public Entity
    {
    public:
        Player(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition);

        void FixedUpdate(float pFixedDeltaTime) override;
        void Update(float pDeltaTime) override;

        void Fire();

        Texture* GetCurrentTexture() const override;
        void OnEntityCollision(Entity* pEntity) override;

        void AddWeapon(std::unique_ptr<Weapon> pWeapon);
        void SwitchWeapon(uint8 pIndex);
        void SwitchToLatestWeapon();

        Weapon* GetCurrentWeapon();
        float GetWeaponSwitchProgress() const;
        float GetWeaponRecoilProgress() const;

        const float FieldOfView{Mau::PI / 2.0f};

        int32 GetHealth() const;
        int32 GetArmor() const;

        int32 GetMaxHealth() const;
        int32 GetMaxArmor() const;

        void AddHealth(int32 pHealth);
        void AddArmor(int32 pArmor);
        void AddAmmo(AmmoType pType, int32 pAmount);

        void Upgrade();

        void AddKey(Key pKey);
        bool HasKey(Key pKey) const;

    private:
        std::vector<std::unique_ptr<Weapon>> mWeapons;
        int8 mCurrentWeaponIndex{-1};
        int8 mNextWeaponIndex{0};

        WeaponSwitchState mWeaponSwitchState{WeaponSwitchState::None};
        float mWeaponSwitchProgress{0.0f};

        WeaponFiringState mWeaponFiringState{ WeaponFiringState::Ready };
        float mWeaponFiringProgress{ 0.0f };

        int32 mHealth{50};
        int32 mArmor{0};

        int32 mMaxHealth{ 100 };
        int32 mMaxArmor{ 100 };
        
        std::set<Key> mKeys;
    };
}

#endif
