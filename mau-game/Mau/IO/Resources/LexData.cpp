#include <cctype>
#include <string>

#include "LexData.h"
#include "Mau/IO/ResourceCache.h"

namespace Mau
{
    LexData::LexData(const std::string& pPath)
        :
        Resource(pPath)
    {
        const std::string text = TextData{ pPath }.GetText();

        // This could have been done more nicely with some sort
        // of a generic state machine. TODO :D

        std::string accumulator{};
        bool stateEscaped = false;
        bool stateInsideString = false;

        for(const char character : text)
        {
            if(isspace(character) && !stateInsideString)
            {
                if(!accumulator.empty())
                {
                    mLexems.push_back(accumulator);
                    accumulator = std::string{};                    
                }
            }
            else
            {
                if (character == '\\')
                {
                    stateEscaped = !stateEscaped;
                }
                else
                {
                    // Spaces inside quotes are not skipped - strings are single lexems.
                    if (character == '\"' && !stateEscaped)
                    {
                        stateInsideString = !stateInsideString;
                    }                    
                    else
                    {
                        accumulator.append(1, character);                        
                    }
                    stateEscaped = false;
                }                
            }
        }
        if(!accumulator.empty())
        {
            mLexems.push_back(accumulator);
        }
    }

    const std::vector<std::string>& LexData::GetLexems() const
    {
        return mLexems;
    }

    std::vector<std::string>::iterator LexData::GetIterator()
    {
        return mLexems.begin();
    }

    int32 LexData::GetInt(size_t pIndex) const
    {
        return std::stoi(GetString(pIndex));
    }

    std::string LexData::GetString(size_t pIndex) const
    {
        if (pIndex >= mLexems.size()) 
        {
            throw Mau::Exception("Unable to access lexem at " + std::to_string(pIndex) + " in " + mPath);
        }
        return mLexems[pIndex];
    }
}
