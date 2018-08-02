#include "PickupKeycard.h"
#include "Mau/States/Gameplay/GameplayState.h"
#include "Mau/Logic/Player.h"

namespace Mau
{
    /*
    * Pickup Keycard Red
    */
    PickupKeycardRed::PickupKeycardRed(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition)
        :
        Pickup(pGameplayState, pLevel, pPosition, pGameplayState.GetEngine().TextureCache.GetResource("pickup_keycard_red.png"))
    {
    }

    void PickupKeycardRed::OnPlayerCollision()
    {
        mGameplayState.DisplayMessage("Picked up the red keycard.");
        mGameplayState.FlashScreen(ScreenFlashPickup);

        Player* player = mLevel.GetPlayer();

        player->AddKey(Key::Red);

        Destroy();
    }

    /*
    * Pickup Keycard Blue
    */
    PickupKeycardBlue::PickupKeycardBlue(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition)
        :
        Pickup(pGameplayState, pLevel, pPosition, pGameplayState.GetEngine().TextureCache.GetResource("pickup_keycard_blue.png"))
    {
    }

    void PickupKeycardBlue::OnPlayerCollision()
    {
        mGameplayState.DisplayMessage("Picked up the blue keycard.");
        mGameplayState.FlashScreen(ScreenFlashPickup);

        Player* player = mLevel.GetPlayer();

        player->AddKey(Key::Blue);

        Destroy();
    }

    /*
    * Pickup Keycard Yellow
    */
    PickupKeycardYellow::PickupKeycardYellow(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition)
        :
        Pickup(pGameplayState, pLevel, pPosition, pGameplayState.GetEngine().TextureCache.GetResource("pickup_keycard_yellow.png"))
    {
    }

    void PickupKeycardYellow::OnPlayerCollision()
    {
        mGameplayState.DisplayMessage("Picked up the yellow keycard.");
        mGameplayState.FlashScreen(ScreenFlashPickup);

        Player* player = mLevel.GetPlayer();

        player->AddKey(Key::Yellow);

        Destroy();
    }
}
