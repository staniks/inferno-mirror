#ifndef INFERNO_STATE_INTRO_H
#define INFERNO_STATE_INTRO_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/States/Story/StoryState.h"

namespace Mau
{
    class IntroState : public StoryState
    {
    public:
        explicit inline IntroState(Engine& pEngine) : StoryState(pEngine)
        {
            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "This game is a work of fiction.",
                    "",
                    "Names, characters, objects and places ",
                    "are either the products of the author's",
                    "imagination or used in a fictitious manner."
                },
                5000
            });
        }

        void OnFinish() override
        {
            mEngine.RequestStateChange(std::make_unique<StateCreator<MainMenuState>>());
        }
    };
}

#endif
