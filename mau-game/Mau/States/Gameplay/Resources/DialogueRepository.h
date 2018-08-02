#ifndef MAU_DIALOGUE_REPOSITORY_H
#define MAU_DIALOGUE_REPOSITORY_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include <unordered_map>
#include "Mau/IO/ResourceCache.h"
#include "Mau/IO/Resources/Texture.h"

namespace Mau
{
    struct Dialogue;
    struct DialogueEntry;
        
    class DialogueRepository
    {
    public:
        explicit DialogueRepository(const std::string& pPath, ResourceCache<Texture>& pTextureCache);

        Dialogue* GetDialogue(const std::string& pDialogueId) const;


    private:
        std::unordered_map<std::string, std::unique_ptr<Dialogue>> mDialogueMap;
        
        static void ProcessLine(DialogueEntry& pEntry, std::string pLine);
    };
}


#endif
