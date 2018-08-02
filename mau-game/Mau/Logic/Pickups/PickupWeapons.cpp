#include "PickupWeapons.h"
#include "Mau/IO/Log.h"
#include "Mau/States/Gameplay/GameplayState.h"
#include "Mau/Logic/Player.h"
#include "Mau/Logic/Weapon.h"
#include "Mau/States/Gameplay/Substates/DialogueState.h"

namespace Mau
{
    PickupWeaponToilet::PickupWeaponToilet(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition)
        :
        Pickup(pGameplayState, pLevel, pPosition, pGameplayState.GetEngine().TextureCache.GetResource("weapon_toilet_pickup.png"))
    {
    }

    void PickupWeaponToilet::OnPlayerCollision()
    {
        mGameplayState.QueueDialogue("toilet_pickup", 0.4f);

        mGameplayState.DisplayMessage("Picked up the Toilet paper shotgun!");
        mGameplayState.FlashScreen(ScreenFlashPickup);

        mLevel.GetPlayer()->AddWeapon(std::make_unique<WeaponToilet>(mGameplayState.GetEngine()));
        mLevel.GetPlayer()->SwitchToLatestWeapon();

        Destroy();
    }

    PickupWeaponPlasma::PickupWeaponPlasma(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition)
        :
        Pickup(pGameplayState, pLevel, pPosition, pGameplayState.GetEngine().TextureCache.GetResource("weapon_plasma_pickup.png"))
    {
    }

    void PickupWeaponPlasma::OnPlayerCollision()
    {
        mGameplayState.QueueDialogue("plasma_pickup", 0.4f);

        mGameplayState.DisplayMessage("Picked up the Samokres-9001 plasma rifle!");
        mGameplayState.FlashScreen(ScreenFlashPickup);
                
        mLevel.GetPlayer()->AddWeapon(std::make_unique<WeaponPlasma>(mGameplayState.GetEngine()));
        mLevel.GetPlayer()->SwitchToLatestWeapon();

        Destroy();
    }

    PickupWeaponRocket::PickupWeaponRocket(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition)
        :
        Pickup(pGameplayState, pLevel, pPosition, pGameplayState.GetEngine().TextureCache.GetResource("weapon_rocket_pickup.png"))
    {
    }

    void PickupWeaponRocket::OnPlayerCollision()
    {
        mGameplayState.QueueDialogue("rocket_pickup", 0.4f);

        mGameplayState.DisplayMessage("Picked up the Mini Rocket Launcher!");
        mGameplayState.FlashScreen(ScreenFlashPickup);
                
        mLevel.GetPlayer()->AddWeapon(std::make_unique<WeaponRocket>(mGameplayState.GetEngine()));
        mLevel.GetPlayer()->SwitchToLatestWeapon();

        Destroy();
    }

    
}
