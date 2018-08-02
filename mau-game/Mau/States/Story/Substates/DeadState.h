#ifndef INFERNO_STATE_DEAD_H
#define INFERNO_STATE_DEAD_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/States/MainMenu/MainMenuState.h"
#include "Mau/States/Story/StoryState.h"

namespace Mau
{
    class DeadState : public StoryState
    {
    public:
        explicit inline DeadState(Engine& pEngine) : StoryState(pEngine)
        {
            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "YOU DIED",
                    "",
                    "[Press ENTER to return to main menu]",
                },
                20000
            });
        }

        void OnFinish() override
        {
            mEngine.RequestStateChange(std::make_unique<StateCreator<MainMenuState>>());
        }
    };
}

#endif
