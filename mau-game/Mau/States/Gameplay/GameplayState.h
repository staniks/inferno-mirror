#ifndef INFERNO_STATE_GAMEPLAY_H
#define INFERNO_STATE_GAMEPLAY_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Mau.h"
#include "Mau/Logic/Level.h"
#include "Mau/States/Gameplay/Resources/DialogueRepository.h"

namespace Mau
{
    class GameplaySubstate;

    constexpr Color ScreenFlashPickup{ 255, 255, 128, 25 };

    class GameplayState : public State
    {
    public:
        explicit GameplayState(Engine& pEngine);

        virtual void HandleEvent(SDL_Event* pEvent) override;
        virtual void FixedUpdate(float pFixedDeltaTime) override;
        virtual void Update(float pDeltaTime) override;
        virtual void Render(float pDeltaTime) override;

        void DisplayMessage(const std::string& pMessage);

        void FlashScreen(const Color& pColor);

        void PushSubstate(std::unique_ptr<GameplaySubstate> pSubstate);
        void PopSubstate();

        void QueueDialogue(std::string pDialogueId, float pTime);

    private:
        void InitializeHorizontalLookupTables();
        void RenderWorld();

    public:
        // Dialogue
        const DialogueRepository DialogueRepository;

    private:
        std::vector<std::unique_ptr<GameplaySubstate>> mSubstateStack;
        Level mLevel;

        // Raycasting        
        std::vector<Color> mHorizontalLookupTable; // precomputed colors for floor and ceiling
        const float mFogReductionFactor = 4.0f;

        // Cosmetics
        float mCurrentWeaponBob{0};

        // Screen flash
        Color mFlashColor{0, 0, 0, 0};
        float mFlashTimer{0.0f};
        float mFlashDuration{0.25f};

        // Messages
        std::string mCurrentMessage{""};
        float mCurrentMessageTimer{0.0f};    

        // Dialogue
        std::vector<std::pair<std::string, float>> mDelayedDialogue;

        //GUI
        std::shared_ptr<Texture> mGuiKeyRed;
        std::shared_ptr<Texture> mGuiKeyBlue;
        std::shared_ptr<Texture> mGuiKeyYellow;
    };

    class GameplaySubstate : public State
    {
    public:
        explicit GameplaySubstate(Engine& pEngine, GameplayState& pGameplayState);
    protected:
        GameplayState& mGameplayState;
    };
}

#endif
