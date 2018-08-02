#ifndef INFERNO_STATE_QUIT_PROMPT_H
#define INFERNO_STATE_QUIT_PROMPT_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Mau.h"
#include "Mau/States/Gameplay/GameplayState.h"

namespace Mau
{
    class QuitPromptState : public GameplaySubstate
    {
    public:
        explicit QuitPromptState(Engine& pEngine, GameplayState& pGameplayState);

        virtual void HandleEvent(SDL_Event* pEvent) override;
        virtual void FixedUpdate(float pFixedDeltaTime) override;
        virtual void Update(float pDeltaTime) override;
        virtual void Render(float pDeltaTime) override;
    };
}

#endif
