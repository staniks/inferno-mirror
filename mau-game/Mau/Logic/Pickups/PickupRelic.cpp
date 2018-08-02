#include "Mau/States/Gameplay/GameplayState.h"
#include "PickupRelic.h"
#include "Mau/Logic/Player.h"

namespace Mau
{
    /*
    * Pickup Relic
    */
    PickupRelic::PickupRelic(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition,
        const std::string& pName, const std::string& pDialogueId)
        :
        Pickup(pGameplayState, pLevel, pPosition, pGameplayState.GetEngine().TextureCache.GetResource("pickup_relic.png")),
        mName(pName),
        mDialogueId(pDialogueId)
    {
    }

    void PickupRelic::OnPlayerCollision()
    {
        static const float delay = 0.4f;

        mGameplayState.QueueDialogue(mDialogueId, delay);
        mGameplayState.QueueDialogue("relic_info", delay);

        mGameplayState.DisplayMessage("Relic found - " + mName + "!");
        mGameplayState.FlashScreen(ScreenFlashPickup);

        mLevel.GetPlayer()->Upgrade();

        Destroy();
    }
}