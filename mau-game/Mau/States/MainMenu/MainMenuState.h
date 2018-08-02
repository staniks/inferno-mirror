#ifndef INFERNO_STATE_MAIN_MENU_H
#define INFERNO_STATE_MAIN_MENU_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Mau.h"

namespace Mau
{
    class MainMenuState;

    struct Menu
    {
        std::string Title;
        struct Entry
        {            
            std::string Text;
            void(MainMenuState::*Action)(void);
        };
        std::vector<Entry> Entries;
    };

    class MainMenuState : public State
    {
    public:
        explicit MainMenuState(Engine& pEngine);

        virtual void HandleEvent(SDL_Event* pEvent) override;
        virtual void FixedUpdate(float pFixedDeltaTime) override;
        virtual void Update(float pDeltaTime) override;
        virtual void Render(float pDeltaTime) override;

        void PushMenu(int32 pMenuIndex);
        void PopMenu();
    private:
        void ActionNewGame();
        void ActionBack();
        void ActionAbout();
        void ActionQuit();
        void ActionStartGame();
        void ActionNothing();

    private:        
        std::shared_ptr<Texture> mBackground;
        std::shared_ptr<BitmapFont> mFont;
        std::shared_ptr<BitmapFont> mSmallFont;

        std::vector<Menu> mMenus;

        std::vector<Menu*> mMenuStack;
        int32 mCurrentMenuOption{0};
        int32 mCurrentMenuSize{0};
        std::vector<int32> mLastMenuOptions; // used in ActionBack, UX
    };
}

#endif
