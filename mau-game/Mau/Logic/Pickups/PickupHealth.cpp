#include "PickupHealth.h"
#include "Mau/States/Gameplay/GameplayState.h"
#include "Mau/Logic/Player.h"

namespace Mau
{
    /*
     * Pickup Health
     */
    PickupHealth::PickupHealth(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition)
        :
        Pickup(pGameplayState, pLevel, pPosition, pGameplayState.GetEngine().TextureCache.GetResource("pickup_health.png"))        
    {
    }

    void PickupHealth::OnPlayerCollision()
    {
        static const int32 HealthAmount = 10;

        Player* player = mLevel.GetPlayer();
        
        if(player->GetHealth() < player->GetMaxHealth())
        {
            mGameplayState.DisplayMessage("Picked up a medkit.");
            mGameplayState.FlashScreen(ScreenFlashPickup);

            mLevel.GetPlayer()->AddHealth(HealthAmount);

            Destroy();
        }        
    }

    /*
    * Pickup Armor
    */
    PickupArmor::PickupArmor(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition)
        :
        Pickup(pGameplayState, pLevel, pPosition, pGameplayState.GetEngine().TextureCache.GetResource("pickup_armor.png"))
    {
    }

    void PickupArmor::OnPlayerCollision()
    {
        static const int32 ArmorAmount = 10;

        Player* player = mLevel.GetPlayer();

        if (player->GetArmor() < player->GetMaxArmor())
        {
            mGameplayState.DisplayMessage("Picked up an armor shard.");
            mGameplayState.FlashScreen(ScreenFlashPickup);

            mLevel.GetPlayer()->AddArmor(ArmorAmount);

            Destroy();
        }
    }
}
