#ifndef MAU_ENGINE_H
#define MAU_ENGINE_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include <memory>
#include <SDL.h>

#include "Mau/Base/RenderDevice.h"
#include "Mau/IO/ResourceCache.h"
#include "Mau/IO/Resources/BitmapFont.h"
#include "Mau/IO/Resources/Texture.h"
#include "Mau/IO/Resources/Sound.h"
#include "Mau/SDL/SDLSystems.h"

namespace Mau
{
    // Forward declarations
    class State;
    class AbstractStateCreator;

    // An instance of the engine. Houses simple state management, framerate-independent 
    // rendering and logic, render device, simple input, etc. 
    class Engine
    {
    public:
        // Initialize an instance of engine. Subsystems must be initialized before.
        explicit Engine(std::shared_ptr<SDLSystemMain> pSdlSystemMain,
                        std::shared_ptr<SDLSystemImage> pSdlSystemImage,
                        std::shared_ptr<SDLSystemMixer> pSdlSystemMixer,
                        std::unique_ptr<AbstractStateCreator> pInitialStateCreator);

        // Request state change at the end of current frame. State instantiation will occur immediately in this method.
        void RequestStateChange(std::unique_ptr<AbstractStateCreator> pNextStateCreator);

        // Returns true if the specified key is held.
        bool GetKeyDown(const SDL_Scancode pScancode) const;

        // Returns the render device ptr. Should not be written to if not locked beforehand (SDL_Texture thread safety mechanism).
        RenderDevice* GetRenderDevice();

        // Request quit at the end of current frame. This will cause main loop to finish and thus terminate the program.
        inline void RequestQuit() { mQuitRequested = true; }

    private:
        // Fixed update is performed at approximately fixed time intervals.
        void FixedUpdate(const float pFixedDeltaTime);
        // Variable update is performed every frame.
        void Update(const float pDeltaTime);
        // Render is performed every frame.
        void Render(const float pDeltaTime);

        // Check if there's a state change request pending. There can be only one request pending at the time.
        void PollStateChange();

        // Render fullscreen fade overlay
        void RenderFadeOverlay(const float pDeltaTime);

    private:
        // Keep in mind order here matters because objects in
        // initialization list are initialized in this order.
        // Is usage of this cpp mechanism in this manner bad practice?

        std::shared_ptr<SDLSystemMain> mSdlSystemMain;
        std::shared_ptr<SDLSystemImage> mSdlSystemImage;
        std::shared_ptr<SDLSystemMixer> mSdlSystemMixer;
        std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> mSdlWindow;
        std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> mSdlRenderer;
        const uint8* mKeyboardState; // SDL array holding key states

        RenderDevice mRenderDevice;

        std::unique_ptr<State> mCurrentState{nullptr};
        std::unique_ptr<State> mNextState{nullptr};

        // Screen fading
        enum class TransitionState { None, In, Out };
        TransitionState mTransitionState{TransitionState::In};
        float mStateTransitionProgress{0.0f};

        bool mQuitRequested{false};


    public:
        uint32 FramesPerSecond{0};
        int32 MouseDeltaX{0};
        const uint32 FixedTimestepMiliseconds = 16; //16ms is 60fps

        //Resource caches
        ResourceCache<Texture> TextureCache;
        ResourceCache<Sound> SoundCache;
        ResourceCache<BitmapFont> FontCache;
    };
}

#endif
