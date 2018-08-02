#ifndef INFERNO_STATE_PRELUDE_H
#define INFERNO_STATE_PRELUDE_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/States/Story/StoryState.h"
#include "Mau/States/Gameplay/GameplayState.h"

namespace Mau
{
    class PreludeState : public StoryState
    {
    public:
        explicit inline PreludeState(Engine& pEngine) : StoryState(pEngine)
        {
            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "Zagreb, 4627 A.D.",
                },
                5000
            });

            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "Science and religion are one.",
                },
                5000
            });

            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "What was once Faculty of Electronic Engineering",
                    "and Computing is now a vast, sprawling complex",
                    "of cathedrals dedicated to worship of the",
                    "Holy Blockchain.",
                },
                10000
            });

            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "In an attempt to improve efficiency of the",
                    "experimental teleportation technology, the",
                    "codepriests have devised an impressive pipeline",
                    "of neural networks, which would allow ",
                    "instantaneous travel to anywhere in the universe.",
                },
                10000
            });

            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "Then, they did something man was ",
                    "never meant to do...",
                },
                5000
            });

            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "They put it on the blockchain.",
                },
                5000
            });

            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "The resulting technological abomination drew",
                    "the attention of extradimensional beings",
                    "resembling creatures from nightmares.",
                },
                10000
            });

            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "Using the newly upgraded teleportation tech,",
                    "the demons quickly overran the complex, causing",
                    "initiation of the emergency evacuation and lockdown.",
                },
                10000
            });

            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "Everyone else is either dead or evacuated.",
                    "You're the only human left in the complex.",
                },
                10000
            });

            AddStoryScreen(StoryScreen{
                std::vector<std::string>{
                    "And you're stuck in a detention cell.",
                },
                5000
            });
        }

        void OnFinish() override
        {            
            mEngine.RequestStateChange(std::make_unique<StateCreator<GameplayState>>());
        }
    };
}

#endif
