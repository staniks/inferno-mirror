#ifndef INFERNO_STATE_STORY_H
#define INFERNO_STATE_STORY_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include <queue>

#include "Mau/Mau.h"

namespace Mau
{
    class StoryState : public State
    {
    public:
        explicit StoryState(Engine& pEngine);

        virtual void HandleEvent(SDL_Event* pEvent) override;
        virtual void FixedUpdate(float pFixedDeltaTime) override;
        virtual void Update(float pDeltaTime) override;
        virtual void Render(float pDeltaTime) override;  

        virtual void OnFinish() = 0;

    private:
        // Fading
        enum class FadeState { In, Out, None };

        FadeState mFadeState{FadeState::In};
        const float mFadeTimeFactor{0.005f};
        float mFadeProgress{0.0f};

        float mFadePauseProgress{0.0f};

    protected:
        // Lines
        struct StoryScreen
        {
            std::vector<std::string> Lines;
            const float DurationMilliseconds;
        };
        std::vector<StoryScreen> mStoryScreens;
        std::vector<StoryScreen>::iterator mStoryScreenIterator;

        void AddStoryScreen(const StoryScreen& pStoryScreen);

    private:
        std::shared_ptr<BitmapFont> mFont;
    };
}

#endif
