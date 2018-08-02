#ifndef MAU_RESOURCE_CACHE_H
#define MAU_RESOURCE_CACHE_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

//#define FINAL_RELEASE

#ifdef FINAL_RELEASE
#define RESOURCE_DIRECTORY_PREFIX "data/"
#else
#define RESOURCE_DIRECTORY_PREFIX "../../mau-assets/"
#endif

#include <memory>
#include <string>
#include <unordered_map>

#include "Mau/Base/Types.h"

namespace Mau
{
    template <class T>
    class ResourceCache
    {
    public:
        std::shared_ptr<T> GetResource(const std::string& pPath);

        void Clear();
    private:
        std::shared_ptr<T> LoadResource(const std::string& pPath);

        std::unordered_map<std::string, std::shared_ptr<T>> mResources{};
    };

    template <class T>
    std::shared_ptr<T> ResourceCache<T>::GetResource(const std::string& pPath)
    {
        const auto iterator = mResources.find(pPath);

        if (iterator != mResources.end())
        {
            return iterator->second;
        }
        else
        {
            return LoadResource(pPath);
        }
    }

    template <class T>
    void ResourceCache<T>::Clear()
    {
        mResources.clear();
    }

    template <class T>
    std::shared_ptr<T> ResourceCache<T>::LoadResource(const std::string& pPath)
    {
        const auto result = mResources.emplace(pPath, std::make_shared<T>(RESOURCE_DIRECTORY_PREFIX + pPath));
        if (result.second == false)
        {
            throw Exception("Unable to cache resource " + pPath);
        }

        // Return the shared pointer
        return result.first->second;
    }
}

#endif
