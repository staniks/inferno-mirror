#include "Player.h"
#include "Mau/States/Gameplay/GameplayState.h"
#include "Projectile.h"

using namespace Mau;

#define HOLSTERING_SPEED 0.005f

namespace Mau
{
    Player::Player(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition)
        :
        Entity(pGameplayState, pLevel, EntityType::Player, pPosition, {0.5f, 0.5f}, false, false)
    {
        SetRotation(-PI / 4.0f);
    }

    void Player::FixedUpdate(float pFixedDeltaTime)
    {
        Entity::FixedUpdate(pFixedDeltaTime);
    }

    void Player::Update(float pDeltaTime)
    {
        Entity::Update(pDeltaTime);

        // SWITCHING
        if(mWeaponSwitchState == WeaponSwitchState::Holstering)
        {    
            mWeaponSwitchProgress = Clamp(mWeaponSwitchProgress + pDeltaTime * HOLSTERING_SPEED, 0.0f, 1.0f);
            if(mWeaponSwitchProgress == 1.0f)
            {
                mWeaponSwitchState = WeaponSwitchState::Arming;
                mCurrentWeaponIndex = mNextWeaponIndex;
            }
        }
        else if(mWeaponSwitchState == WeaponSwitchState::Arming)
        {
            mWeaponSwitchProgress = Clamp(mWeaponSwitchProgress - pDeltaTime * HOLSTERING_SPEED, 0.0f, 1.0f);
            if (mWeaponSwitchProgress == 0.0f)
            {
                mWeaponSwitchState = WeaponSwitchState::None;
            }
        }

        // FIRING
        if(GetCurrentWeapon())
        {
            if (mWeaponFiringState == WeaponFiringState::Recoiling)
            {
                mWeaponFiringProgress = Clamp(mWeaponFiringProgress + pDeltaTime * GetCurrentWeapon()->RecoilSpeed, 0.0f, 1.0f);
                if (mWeaponFiringProgress == 1.0f)
                {
                    mWeaponFiringState = WeaponFiringState::Recovering;
                }
            }
            else if (mWeaponFiringState == WeaponFiringState::Recovering)
            {
                mWeaponFiringProgress = Clamp(mWeaponFiringProgress - pDeltaTime * GetCurrentWeapon()->RecoverySpeed, 0.0f, 1.0f);
                if (mWeaponFiringProgress == 0.0f)
                {
                    mWeaponFiringState = WeaponFiringState::Ready;
                }
            }
        }        
    }

    void Player::Fire()
    {
        if(GetCurrentWeapon() && mWeaponFiringState == WeaponFiringState::Ready && GetCurrentWeapon()->GetAmmo() > 0)
        {
            mWeaponFiringState = WeaponFiringState::Recoiling;

            //Vec2f projectilePosition = GetPosition() + GetDirection() * 1.0f + GetRight() * 0.25f;
            Vec2f projectilePosition = GetPosition() + GetDirection() * 0.5f + GetRight() * 0.20f;

            const auto raycastInfo = mLevel.RaycastWall(GetPosition(), (projectilePosition - GetPosition()).Normalized());

            if((raycastInfo.HitPosition - GetPosition()).Length() <= (projectilePosition - GetPosition()).Length())
            {
                projectilePosition = raycastInfo.HitPosition;
            }

            GetCurrentWeapon()->OnFire(mGameplayState, mLevel, projectilePosition, GetDirection(), GetRight());
        }
    }

    Texture* Player::GetCurrentTexture() const
    {
        return nullptr;
    }

    void Player::OnEntityCollision(Entity* pEntity)
    {
    }

    void Player::AddWeapon(std::unique_ptr<Weapon> pWeapon)
    {
        mWeapons.push_back(std::move(pWeapon));
    }

    void Player::SwitchWeapon(uint8 pIndex)
    {
        if (pIndex >= mWeapons.size() || pIndex == mCurrentWeaponIndex)
            return;

        mNextWeaponIndex = pIndex;

        mWeaponSwitchState = WeaponSwitchState::Holstering;
    }

    void Player::SwitchToLatestWeapon()
    {
        SwitchWeapon(mWeapons.size() - 1);
    }

    Weapon* Player::GetCurrentWeapon()
    {
        if (mWeapons.empty() || mCurrentWeaponIndex < 0)
            return nullptr;

        return mWeapons[mCurrentWeaponIndex].get();
    }

    float Player::GetWeaponSwitchProgress() const
    {
        return mWeaponSwitchProgress;
    }

    float Player::GetWeaponRecoilProgress() const
    {
        return mWeaponFiringProgress;
    }

    int32 Player::GetHealth() const
    {
        return mHealth;
    }

    int32 Player::GetArmor() const
    {
        return mArmor;
    }

    int32 Player::GetMaxHealth() const
    {
        return mMaxHealth;
    }

    int32 Player::GetMaxArmor() const
    {
        return mMaxArmor;
    }

    void Player::AddHealth(int32 pHealth)
    {
        if(pHealth < 0)
        {
            if(mArmor > 0)
            {
                mArmor = Clamp(mArmor + pHealth, 0, mMaxArmor);
                mHealth = Clamp(mHealth + pHealth / 2, 0, mMaxHealth);
                return;
            }
        }

        mHealth = Clamp(mHealth + pHealth, 0, mMaxHealth);        
    }

    void Player::AddArmor(int32 pArmor)
    {
        mArmor = Clamp(mArmor + pArmor, 0, mMaxArmor);
    }

    void Player::AddAmmo(AmmoType pType, int32 pAmount)
    {
        for(auto& weapon : mWeapons)
        {
            if(weapon->GetAmmoType() == pType)
            {
                weapon->AddAmmo(pAmount);
                break;
            }
        }
    }

    void Player::Upgrade()
    {
        mMaxHealth += 5;
        mMaxArmor += 5;

        // too OP?
       /* mHealth = mMaxHealth;
        mArmor = mMaxArmor;*/
    }

    void Player::AddKey(Key pKey)
    {
        mKeys.insert(pKey);
    }

    bool Player::HasKey(Key pKey) const
    {
        return mKeys.count(pKey) > 0;
    }
}

