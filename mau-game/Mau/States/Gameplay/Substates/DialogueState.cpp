#include "Mau/States/Gameplay/Substates/DialogueState.h"

namespace Mau
{
    DialogueState::DialogueState(Engine& pEngine, GameplayState& pGameplayState, const std::string& pDialogueId)
        :
        GameplaySubstate(pEngine, pGameplayState),
        mDialogue(pGameplayState.DialogueRepository.GetDialogue(pDialogueId)),
        mDialogueIterator(mDialogue->Entries.begin())
    {
        
    }

    void DialogueState::HandleEvent(SDL_Event* pEvent)
    {
        if (pEvent->type == SDL_KEYDOWN)
        {
            switch (pEvent->key.keysym.sym)
            {
            case SDLK_RETURN: AdvanceDialogue(); break;
            case SDLK_KP_ENTER: AdvanceDialogue(); break;
            case SDLK_SPACE: AdvanceDialogue(); break;
            default: break;
            }
        }
    }

    void DialogueState::FixedUpdate(float pFixedDeltaTime)
    {
    }

    void DialogueState::Update(float pDeltaTime)
    {
        
    }

    void DialogueState::Render(float pDeltaTime)
    {
        const auto renderDevice = mEngine.GetRenderDevice();

        if (mDialogueIterator == mDialogue->Entries.end())
            return;

        DialogueEntry& entry = *mDialogueIterator;
        
        const auto font = mEngine.FontCache.GetResource("font_small.mau").get();
        const auto font_red = mEngine.FontCache.GetResource("font_small_red.mau").get();
        const auto frame = mEngine.TextureCache.GetResource("dialogue_frame.png").get();

        const Vec2i dialogueBoxPosition{ 24, 80 };
        const Vec2i dialoguePortraitSize{ 70, 70 };

        renderDevice->RenderTexture(entry.Portrait.get(), dialogueBoxPosition);
        renderDevice->RenderTexture(frame, dialogueBoxPosition);

        renderDevice->RenderRect(dialogueBoxPosition + Vec2i{ dialoguePortraitSize.x, 0 }, Vec2i{
            renderDevice->Width - dialogueBoxPosition.x * 2 - dialoguePortraitSize.x, dialoguePortraitSize.y
            }, Color{ 0, 0, 0, 196 });

        const Vec2i textPosition = dialogueBoxPosition + Vec2i{ dialoguePortraitSize.x, 0 } + Vec2i{ 4, 4 };

        renderDevice->RenderString(font_red, textPosition, entry.Title);

        int32 lineOffset = 0;
        int characterCount = 0;
        for(auto& line : entry.Content)
        {
            for(int32 i=0; i<line.length(); ++i)
            {
                if(mCurrentCharacter > characterCount)
                    renderDevice->RenderCharacter(font, textPosition + Vec2i{ i * font->CharacterSize.x, font->CharacterSize.y + lineOffset }, line[i]);

                ++characterCount;
            }
            lineOffset += font->CharacterSize.y;
        }

        mCurrentCharacter += pDeltaTime / 20.0f;
        if (mCurrentCharacter >= characterCount)
            mCurrentCharacter = characterCount;
    }

    void DialogueState::AdvanceDialogue()
    {
        if(mCurrentCharacter >= GetCurrentCharacterCount())
        {
            mCurrentCharacter = 0;
            ++mDialogueIterator;
            if (mDialogueIterator == mDialogue->Entries.end())
            {
                mGameplayState.PopSubstate();
            }
        }
        else
        {
            mCurrentCharacter = GetCurrentCharacterCount();
        }
    }

    int32 DialogueState::GetCurrentCharacterCount() const
    {
        int32 characterCount = 0;
        for (auto& line : (*mDialogueIterator).Content)
        {
            characterCount += line.length();
        }
        return characterCount;
    }
}
