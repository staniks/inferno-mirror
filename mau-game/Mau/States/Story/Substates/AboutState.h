#ifndef INFERNO_STATE_ABOUT_H
#define INFERNO_STATE_ABOUT_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/States/MainMenu/MainMenuState.h"
#include "Mau/States/Story/StoryState.h"

namespace Mau
{
    class AboutState : public StoryState
    {
    public:
        explicit inline AboutState(Engine& pEngine) : StoryState(pEngine)
        {
            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "I wrote Inferno to further teach myself",
                    "C++ and game development in general.",
                    "",
                    "It's more of a portfolio project than a",
                    "complete game, so it's designed to be",
                    "completed in a single playthrough.",
                    "",
                    "The source is available on my git.",
                    "https://github.com/staniks",
                    "",
                    "Have fun.",
                    "",
                    "",
                    "               Developer, Marko Stanic",
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
