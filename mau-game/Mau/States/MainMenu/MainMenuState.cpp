#include "Mau/States/Gameplay/Substates/DialogueState.h"
#include "Mau/States/MainMenu/MainMenuState.h"
#include "Mau/States/Story/Substates/AboutState.h"
#include "Mau/States/Story/Substates/PreludeState.h"

#define MENU_MAIN 0
#define MENU_NEWGAME 1

namespace Mau
{
    MainMenuState::MainMenuState(Engine& pEngine)
        :
        State(pEngine),
        mBackground(mEngine.TextureCache.GetResource("main_menu_vibrant.png")),
        mFont(mEngine.FontCache.GetResource("font_red.mau")),
        mSmallFont(mEngine.FontCache.GetResource("font_small_red.mau"))
    {
        mMenus.push_back(
            Menu
            {
                "Main Menu",
                std::vector<Menu::Entry>
                {
                    Menu::Entry{"NEW GAME", &MainMenuState::ActionNewGame},
                    Menu::Entry{"ABOUT", &MainMenuState::ActionAbout},
                    Menu::Entry{"QUIT", &MainMenuState::ActionQuit},
                }
            }
        );

        mMenus.push_back(
            Menu
            {
                "Episode Select",
                std::vector<Menu::Entry>
                {
                    Menu::Entry{"PRISON BREAK", &MainMenuState::ActionStartGame},
                    Menu::Entry{"-- NOT AVAILABLE --", &MainMenuState::ActionNothing},
                    Menu::Entry{"-- NOT AVAILABLE --", &MainMenuState::ActionNothing},
                    Menu::Entry{"BACK", &MainMenuState::ActionBack},
                }
            }
        );

        PushMenu(MENU_MAIN);
    }

    void MainMenuState::HandleEvent(SDL_Event* pEvent)
    {
        if (pEvent->type == SDL_KEYDOWN)
        {
            if (pEvent->key.keysym.sym == SDLK_DOWN)
            {
                mCurrentMenuOption = (++mCurrentMenuOption) % mCurrentMenuSize;
            }
            else if (pEvent->key.keysym.sym == SDLK_UP)
            {
                mCurrentMenuOption = ((--mCurrentMenuOption) % mCurrentMenuSize + mCurrentMenuSize) % mCurrentMenuSize;
            }
            else if (pEvent->key.keysym.sym == SDLK_RETURN)
            {
                (this->*mMenuStack.back()->Entries[mCurrentMenuOption].Action)();
            }
        }
    }

    void MainMenuState::FixedUpdate(float pFixedDeltaTime)
    {
    }

    void MainMenuState::Update(float pDeltaTime)
    {
    }

    void MainMenuState::Render(float pDeltaTime)
    {
        RenderDevice* renderDevice = mEngine.GetRenderDevice();

        renderDevice->RenderTexture(mBackground.get(), {0, 0});

        const int32 textHeight = mFont->GetTexture()->GetHeight() / FONT_CHARACTERS_Y;
        const int32 textX = 35;
        int32 textY = 63;

        for (int y = textY; y < textY + textHeight; ++y)
        {
            for (int x = 0; x < renderDevice->Width; ++x)
            {
                const float intensity = 1.0f - static_cast<float>(x) / renderDevice->Width;
                renderDevice->RenderPixelAlphaBlend({x, y}, {0, 0, 0, static_cast<byte>(128 * intensity)});
            }
        }

        renderDevice->RenderString(mFont.get(), {textX, textY}, mMenuStack.back()->Title);

        textY += textHeight * 2;

        // Render overlay
        for (int y = textY; y < textY + mCurrentMenuSize * textHeight; ++y)
        {
            for (int x = 0; x < renderDevice->Width; ++x)
            {
                const float intensity = 1.0f - static_cast<float>(x) / renderDevice->Width;
                renderDevice->RenderPixelAlphaBlend({x, y}, {0, 0, 0, static_cast<byte>(128 * intensity)});
            }
        }

        renderDevice->RenderCharacter(mFont.get(), {textX - 8, textY + mCurrentMenuOption * textHeight}, 16);

        for (int i = 0; i < mCurrentMenuSize; ++i)
        {
            renderDevice->RenderString(mFont.get(), {textX, textY + i * textHeight},
                                       mMenuStack.back()->Entries[i].Text);
        }


        renderDevice->RenderString(mSmallFont.get(),
                                   {
                                       2,
                                       renderDevice->Height - mSmallFont->GetTexture()->GetHeight() / FONT_CHARACTERS_Y
                                       - 2
                                   },
                                   "staniks.github.io/inferno");
    }

    void MainMenuState::PushMenu(int32 pMenuIndex)
    {
        mMenuStack.push_back(&mMenus[pMenuIndex]);
        mLastMenuOptions.push_back(mCurrentMenuOption);
        mCurrentMenuOption = 0;
        mCurrentMenuSize = mMenus[pMenuIndex].Entries.size();
    }

    void MainMenuState::PopMenu()
    {
        mMenuStack.pop_back();
        mCurrentMenuSize = mMenuStack.back()->Entries.size();
        mCurrentMenuOption = mLastMenuOptions.back();
        mLastMenuOptions.pop_back();
    }

    void MainMenuState::ActionNewGame()
    {
        PushMenu(MENU_NEWGAME);
    }

    void MainMenuState::ActionBack()
    {
        PopMenu();
    }

    void MainMenuState::ActionAbout()
    {
        mEngine.RequestStateChange(std::make_unique<StateCreator<AboutState>>());
    }

    void MainMenuState::ActionQuit()
    {
        mEngine.RequestQuit();
    }

    void MainMenuState::ActionStartGame()
    {
        mEngine.RequestStateChange(std::make_unique<StateCreator<PreludeState>>());
    }

    void MainMenuState::ActionNothing()
    {
    }
}
