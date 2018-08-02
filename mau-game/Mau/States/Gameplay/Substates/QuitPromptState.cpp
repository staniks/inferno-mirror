#include "Mau/States/Gameplay/Substates/QuitPromptState.h"
#include "Mau/States/MainMenu/MainMenuState.h"

namespace Mau
{
    QuitPromptState::QuitPromptState(Engine& pEngine, GameplayState& pGameplayState)
        :
        GameplaySubstate(pEngine, pGameplayState)
    {
    }

    void QuitPromptState::HandleEvent(SDL_Event* pEvent)
    {
        if (pEvent->type == SDL_KEYDOWN)
        {
            if (pEvent->key.keysym.sym == SDLK_n)
            {
                mGameplayState.PopSubstate();
            }
            else if (pEvent->key.keysym.sym == SDLK_y || pEvent->key.keysym.sym == SDLK_z) //Why both y and z? Croatian gamers will know.
            {
                mEngine.RequestStateChange(std::make_unique<StateCreator<MainMenuState>>());
            }
        }
    }

    void QuitPromptState::FixedUpdate(float pFixedDeltaTime)
    {
    }

    void QuitPromptState::Update(float pDeltaTime)
    {
    }

    void QuitPromptState::Render(float pDeltaTime)
    {
        const auto renderDevice = mEngine.GetRenderDevice();
        const auto font = mEngine.FontCache.GetResource("font_small.mau").get();

        const int32 promptHeight = font->CharacterSize.y * 4;
        const int32 promptY = renderDevice->Height / 2 - promptHeight / 2;

        renderDevice->RenderRect(Vec2i{0, promptY}, Vec2i{renderDevice->Width, promptHeight}, Color{0, 0, 0, 196});

        const std::string promptText = "Are you sure you want to quit?";
        renderDevice->RenderString(font, Vec2i{
            renderDevice->Width / 2 - static_cast<int32>(promptText.length()) * font->CharacterSize.x / 2,
            promptY + font->CharacterSize.y
        }, promptText);

        const std::string ynText = "y/n";
        renderDevice->RenderString(font, Vec2i{
            renderDevice->Width / 2 - static_cast<int32>(ynText.length()) * font->CharacterSize.x / 2,
            promptY + font->CharacterSize.y * 2
        }, ynText);
    }
}
