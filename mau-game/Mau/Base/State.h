#ifndef MAU_STATE_H
#define MAU_STATE_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include <memory>

#include "Mau/Base/Engine.h"

namespace Mau
{
    class State
    {
    public:
        // Use the constructor to load any resources - prefer RAII.
        explicit State(Engine& pEngine);
        virtual  ~State() = default;
        
        virtual void HandleEvent(SDL_Event* pEvent) = 0;
        virtual void FixedUpdate(float pFixedDeltaTime) = 0;
        virtual void Update(float pDeltaTime) = 0;
        virtual void Render(float pDeltaTime) = 0;

        Engine& GetEngine() const;

    protected:
        Engine& mEngine;
    };

    class AbstractStateCreator
    {
    public:
        virtual ~AbstractStateCreator() = default;

        virtual std::unique_ptr<State> Create(Engine& pEngine) const = 0;
    };

    template <class T>
    class StateCreator : public AbstractStateCreator
    {
    public:
        std::unique_ptr<State> Create(Engine& pEngine) const override
        {
            return std::make_unique<T>(pEngine);
        }
    };
}

#endif
