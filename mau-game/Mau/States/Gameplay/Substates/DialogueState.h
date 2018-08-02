#ifndef INFERNO_STATE_DIALOGUE_H
#define INFERNO_STATE_DIALOGUE_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Mau.h"
#include "Mau/States/Gameplay/GameplayState.h"

namespace Mau
{
    struct DialogueEntry
    {
        std::shared_ptr<Texture> Portrait;
        std::string Title;
        std::vector<std::string> Content;
    };

    struct Dialogue
    {
        std::vector<DialogueEntry> Entries;
    };

    class DialogueState : public GameplaySubstate
    {
    public:
        explicit DialogueState(Engine& pEngine, GameplayState& pGameplayState, const std::string& pDialogueId);

        virtual void HandleEvent(SDL_Event* pEvent) override;
        virtual void FixedUpdate(float pFixedDeltaTime) override;
        virtual void Update(float pDeltaTime) override;
        virtual void Render(float pDeltaTime) override;

    private:
        void AdvanceDialogue();

        int32 GetCurrentCharacterCount() const;

    private:
        Dialogue* mDialogue;
        std::vector<DialogueEntry>::iterator mDialogueIterator;
        float mCurrentCharacter{ 0 };
    };
}

#endif
