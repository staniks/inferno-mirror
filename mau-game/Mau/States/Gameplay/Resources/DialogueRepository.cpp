#include <iterator>
#include <sstream>

#include "DialogueRepository.h"
#include "Mau/IO/Resources/LexData.h"
#include "Mau/States/Gameplay/Substates/DialogueState.h"
#include <deque>

namespace Mau
{
    DialogueRepository::DialogueRepository(const std::string& pPath, ResourceCache<Texture>& pTextureCache)
    {
        LexData lexData{pPath};

        Dialogue dialogue;
        std::string dialogueKey;
        DialogueEntry entry;

        // todo: error handling

        auto iterator = lexData.GetIterator();
        while (iterator != lexData.GetLexems().end())
        {
            if (*iterator == "BEGIN_DIALOGUE")
            {
                dialogue = Dialogue{};
                ++iterator;
                dialogueKey = *iterator;
                ++iterator;
            }
            else if (*iterator == "END_DIALOGUE")
            {
                mDialogueMap[dialogueKey] = std::make_unique<Dialogue>(dialogue);
                ++iterator;
            }
            else
            {
                if (*iterator == "BEGIN_ENTRY")
                {
                    entry = {};
                    ++iterator;
                    entry.Portrait = pTextureCache.GetResource(*iterator);
                    ++iterator;
                    entry.Title = *iterator;
                    ++iterator;
                }
                else if (*iterator == "END_ENTRY")
                {
                    dialogue.Entries.push_back(entry);
                    ++iterator;
                }
                else
                {
                    ProcessLine(entry, *iterator);
                    ++iterator;
                }
            }
        }
    }

    Dialogue* DialogueRepository::GetDialogue(const std::string& pDialogueId) const
    {
        return mDialogueMap.at(pDialogueId).get();
    }

    void DialogueRepository::ProcessLine(DialogueEntry& pEntry, std::string pLine)
    {
        std::istringstream iss(pLine);
        std::vector<std::string> tokens{
            std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{}
        };

        if(tokens.empty())
        {
            pEntry.Content.emplace_back("");
            return;
        }

        std::string currentLine{};
        int32 currentIndex = 0;
        const int32 maxIndex = 33;

        for(auto& token : tokens)
        {
            if (currentIndex + token.size() < maxIndex)
            {
                currentLine += token + " ";
                currentIndex += token.size() + 1;
            }
            else
            {
                pEntry.Content.push_back(currentLine);
                currentLine = token + " ";
                currentIndex = token.size() + 1;
            }
        }

        if(currentLine.length() > 0)
            pEntry.Content.push_back(currentLine);
    }
}
