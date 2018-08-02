#include "PickupExit.h"
#include "Mau/States/Gameplay/GameplayState.h"
#include "Mau/Logic/Player.h"
#include "Mau/States/Story/Substates/FinishState.h"

namespace Mau
{
    /*
    * Pickup Exit
    */
    PickupExit::PickupExit(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition)
        :
        Pickup(pGameplayState, pLevel, pPosition, nullptr)
    {
    }

    void PickupExit::OnPlayerCollision()
    {
        mGameplayState.GetEngine().RequestStateChange(std::make_unique<StateCreator<FinishState>>());
    }
}
