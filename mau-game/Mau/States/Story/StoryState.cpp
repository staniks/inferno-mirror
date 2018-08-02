#include "Mau/States/MainMenu/MainMenuState.h"
#include "Mau/States/Story/StoryState.h"
#include "Mau/Math/Math.h"

#define MENU_MAIN 0
#define MENU_NEWGAME 1
#define MENU_OPTIONS 2
#define MENU_ABOUT 3

//#define ENABLE_STORY_TIMESWITCH

namespace Mau
{
    StoryState::StoryState(Engine& pEngine)
        :
        State(pEngine),
        mFont(mEngine.FontCache.GetResource("font_small_red.mau"))
    {
        
    }

    void StoryState::HandleEvent(SDL_Event* pEvent)
    {
        if (pEvent->type == SDL_KEYDOWN)
        {
            //skip current story screen
            if (pEvent->key.keysym.sym == SDLK_RETURN || pEvent->key.keysym.sym == SDLK_KP_ENTER || pEvent->key.keysym.sym == SDLK_SPACE)
            {
                if (mFadeState == FadeState::None)
                {
                    mFadePauseProgress = 0.0f;
                    mFadeState = FadeState::Out;
                }
            }
        }
    }

    void StoryState::FixedUpdate(float pFixedDeltaTime)
    {
    }

    void StoryState::Update(float pDeltaTime)
    {
        if (mFadeState == FadeState::None)
        {
#ifdef ENABLE_STORY_TIMESWITCH
            mFadePauseProgress += pDeltaTime;
#endif
            if (mFadePauseProgress >= (*mStoryScreenIterator).DurationMilliseconds)
            {
                mFadePauseProgress = 0.0f;
                mFadeState = FadeState::Out;
            }
        }
        else
        {
            mFadeProgress = Clamp(mFadeProgress + mFadeTimeFactor * pDeltaTime, 0.0f, 1.0f);

            if (mFadeProgress >= 1.0f)
            {
                mFadeProgress = 0;
                mFadeState = mFadeState == FadeState::In ? FadeState::None : FadeState::In;

                if (mFadeState == FadeState::In)
                {
                    ++mStoryScreenIterator;
                    if (mStoryScreenIterator == mStoryScreens.end())
                    {
                        OnFinish();
                    }
                }
            }
        }
    }

    void StoryState::Render(float pDeltaTime)
    {
        RenderDevice* renderDevice = mEngine.GetRenderDevice();

        renderDevice->RenderFill({0, 0, 0, 255});

        StoryScreen& currentScreen = mStoryScreenIterator == mStoryScreens.end()
                                         ? mStoryScreens.back()
                                         : *mStoryScreenIterator;

        const int32 fontWidth = mFont->GetTexture()->GetWidth() / FONT_CHARACTERS_X;
        const int32 fontHeight = mFont->GetTexture()->GetHeight() / FONT_CHARACTERS_Y;

        for (int32 i = 0; i < currentScreen.Lines.size(); ++i)
        {
            const int32 textWidth = fontWidth * currentScreen.Lines[i].length();

            const int32 textX = renderDevice->Width / 2 - textWidth / 2;
            const int32 textY = renderDevice->Height / 2 - currentScreen.Lines.size() * fontHeight / 2 + i * fontHeight;

            renderDevice->RenderString(mFont.get(), {textX, textY}, currentScreen.Lines[i]);
        }


        if (mFadeState != FadeState::None)
        {
            const uint8 alpha = mFadeState == FadeState::Out ? mFadeProgress * 255 : (1.0f - mFadeProgress) * 255;
            renderDevice->RenderFill({0, 0, 0, alpha});
        }
    }

    void StoryState::AddStoryScreen(const StoryScreen& pStoryScreen)
    {
        mStoryScreens.push_back(pStoryScreen);
        mStoryScreenIterator = mStoryScreens.begin();
    }
}
