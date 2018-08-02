#ifndef INFERNO_STATE_FINISH_H
#define INFERNO_STATE_FINISH_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/States/Story/StoryState.h"
#include "Mau/States/MainMenu/MainMenuState.h"

namespace Mau
{
    class FinishState : public StoryState
    {
    public:
        explicit inline FinishState(Engine& pEngine) : StoryState(pEngine)
        {
            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "As you escape the demon-infested facility,",
                    "you start feeling relieved, only to find",
                    "that demons brought their reality with them.",
                },
                5000
            });

            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "Countless fiery islands fill the sky,",
                    "each writhing with thousands of demons.",
                },
                5000
            });

            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "This is gonna be a long day.",
                },
                5000
            });

            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "But that's a story for another time. ",
                    " ",
                    "Perhaps, Inferno VR or Inferno Battle Royale."
                },
                5000
            });

            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "Thanks for playing!",
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
