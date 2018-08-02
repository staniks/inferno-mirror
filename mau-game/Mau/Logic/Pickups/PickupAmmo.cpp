#include "PickupAmmo.h"
#include "Mau/States/Gameplay/GameplayState.h"
#include "Mau/Logic/Player.h"

namespace Mau
{
    /*
     * PICKUP AMMO TOILET
     */
    PickupAmmoToilet::PickupAmmoToilet(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition)
        :
        Pickup(pGameplayState, pLevel, pPosition,
               pGameplayState.GetEngine().TextureCache.GetResource("pickup_paper.png"))
    {
    }

    void PickupAmmoToilet::OnPlayerCollision()
    {
        static const int32 AmmoAmount = 8;

        Player* player = mLevel.GetPlayer();
        mGameplayState.DisplayMessage("Picked up some toilet paper.");
        mGameplayState.FlashScreen(ScreenFlashPickup);

        mLevel.GetPlayer()->AddAmmo(AmmoType::Toilet, AmmoAmount);

        Destroy();
    }

    /*
    * PICKUP AMMO PLASMA
    */
    PickupAmmoPlasma::PickupAmmoPlasma(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition)
        :
        Pickup(pGameplayState, pLevel, pPosition,
            pGameplayState.GetEngine().TextureCache.GetResource("pickup_plasma.png"))
    {
    }

    void PickupAmmoPlasma::OnPlayerCollision()
    {
        static const int32 AmmoAmount = 16;

        Player* player = mLevel.GetPlayer();
        mGameplayState.DisplayMessage("Picked up some plasma rifle ammo.");
        mGameplayState.FlashScreen(ScreenFlashPickup);

        mLevel.GetPlayer()->AddAmmo(AmmoType::Plasma, AmmoAmount);

        Destroy();
    }

    /*
    * PICKUP AMMO ROCKET
    */
    PickupAmmoRocket::PickupAmmoRocket(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition)
        :
        Pickup(pGameplayState, pLevel, pPosition,
            pGameplayState.GetEngine().TextureCache.GetResource("pickup_rockets.png"))
    {
    }

    void PickupAmmoRocket::OnPlayerCollision()
    {
        static const int32 AmmoAmount = 4;

        Player* player = mLevel.GetPlayer();
        mGameplayState.DisplayMessage("Picked up some rockets.");
        mGameplayState.FlashScreen(ScreenFlashPickup);

        mLevel.GetPlayer()->AddAmmo(AmmoType::Rocket, AmmoAmount);

        Destroy();
    }
}
