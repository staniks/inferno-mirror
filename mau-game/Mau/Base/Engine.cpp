#include <algorithm>

#include "Mau/Base/Engine.h"
#include "Mau/Base/State.h"
#include "Mau/IO/Log.h"
#include "Mau/Math/Math.h"

#define RES_FACTOR 2

#define RES_X 320 * RES_FACTOR
#define RES_Y 200 * RES_FACTOR

#define INFERNO_FULLSCREEN

namespace Mau
{
    Engine::Engine(std::shared_ptr<SDLSystemMain> pSdlSystemMain,
                   std::shared_ptr<SDLSystemImage> pSdlSystemImage,
                   std::shared_ptr<SDLSystemMixer> pSdlSystemMixer,
                   std::unique_ptr<AbstractStateCreator> pInitialStateCreator)
        :
        mSdlSystemMain(std::move(pSdlSystemMain)),
        mSdlSystemImage(std::move(pSdlSystemImage)),
        mSdlSystemMixer(std::move(pSdlSystemMixer)),
        mSdlWindow(SDL_CreateWindow("Inferno",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    RES_X,
                                    RES_Y,
#ifdef INFERNO_FULLSCREEN
                                    SDL_WINDOW_HIDDEN | SDL_WINDOW_FULLSCREEN_DESKTOP),
#else
                                    SDL_WINDOW_HIDDEN),
#endif
                   SDL_DestroyWindow),
        mSdlRenderer(SDL_CreateRenderer(mSdlWindow.get(),
                                        -1,
                                        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
                     SDL_DestroyRenderer),
        mKeyboardState(SDL_GetKeyboardState(nullptr)),
        mRenderDevice(mSdlRenderer.get(),
                      320,
                      200)
    {
        mCurrentState = pInitialStateCreator->Create(*this);

        // Make sure we're displaying target resolution at any desktop resolution (with letterboxing if needed)
        SDL_RenderSetLogicalSize(mSdlRenderer.get(), mRenderDevice.Width, mRenderDevice.Height);
        SDL_SetRenderDrawBlendMode(mSdlRenderer.get(), SDL_BLENDMODE_BLEND);

        SDL_ShowWindow(mSdlWindow.get());
        SDL_ShowCursor(SDL_DISABLE);
        SDL_SetWindowGrab(mSdlWindow.get(), SDL_TRUE);
        SDL_SetRelativeMouseMode(SDL_TRUE);

        // Initialize game-loop related variables        
        uint32 lastFrameTimeMiliseconds = SDL_GetTicks();
        uint32 frameLagMiliseconds = 0;

        SDL_Event event;

        // Begin main game loop
        while (!mQuitRequested)
        {
            // Handle events first
            while (SDL_PollEvent(&event) > 0)
            {
                if (event.type == SDL_QUIT)
                {
                    mQuitRequested = true;
                }
                else
                {
                    if (mTransitionState == TransitionState::None)
                    {
                        mCurrentState->HandleEvent(&event);
                    }
                }
            }

            // Calculate timestep-related values
            const uint32 currentFrameTimeMiliseconds = SDL_GetTicks();
            const uint32 deltaTimeMiliseconds = currentFrameTimeMiliseconds - lastFrameTimeMiliseconds;
            lastFrameTimeMiliseconds = currentFrameTimeMiliseconds;
            frameLagMiliseconds += deltaTimeMiliseconds;

            // Calculate FPS (only for information, not actually used in calculations)
            FramesPerSecond = static_cast<uint32>(1000.0f / static_cast<float>(deltaTimeMiliseconds));

            SDL_GetRelativeMouseState(&MouseDeltaX, nullptr);

            // Perform fixed update of current state, if it's the time
            while (frameLagMiliseconds >= FixedTimestepMiliseconds)
            {
                frameLagMiliseconds -= FixedTimestepMiliseconds;

                FixedUpdate(static_cast<float>(FixedTimestepMiliseconds));
            }

            // Perform variable update of current state
            Update(static_cast<float>(deltaTimeMiliseconds));

            // Lock the render device, then perform render of current state            
            {
                RenderDevice::Lock lock{&mRenderDevice};
                Render(static_cast<float>(deltaTimeMiliseconds));
            }

            // Render the texture
            SDL_RenderCopy(mSdlRenderer.get(), mRenderDevice.GetTexture(), nullptr, nullptr);

            RenderFadeOverlay(static_cast<float>(deltaTimeMiliseconds));

            // Flip buffers
            SDL_RenderPresent(mSdlRenderer.get());

            PollStateChange();
        }
    }

    void Engine::FixedUpdate(const float pFixedDeltaTime)
    {
        if (mTransitionState != TransitionState::None)
            return;

        mCurrentState->FixedUpdate(pFixedDeltaTime);
    }

    void Engine::Update(const float pDeltaTime)
    {
        if (mTransitionState != TransitionState::None)
            return;

        mCurrentState->Update(pDeltaTime);
    }

    void Engine::Render(const float pDeltaTime)
    {
        mCurrentState->Render(pDeltaTime);
    }

    void Engine::PollStateChange()
    {
        if (mNextState != nullptr)
        {
            if (mTransitionState == TransitionState::None)
            {
                mTransitionState = TransitionState::Out;
            }
            else if (mStateTransitionProgress >= 1.0f)
            {
                mCurrentState = std::move(mNextState);
                mNextState = nullptr;

                mTransitionState = TransitionState::In;
                mStateTransitionProgress = 0.0f;
            }
        }
    }

    void Engine::RenderFadeOverlay(const float pDeltaTime)
    {
        if (mTransitionState == TransitionState::None)
            return;

        if (mTransitionState == TransitionState::In)
        {
            if (mStateTransitionProgress >= 1.0f)
            {
                mTransitionState = TransitionState::None;
                mStateTransitionProgress = 0.0f;
                return;
            }
        }

        mStateTransitionProgress = Clamp(mStateTransitionProgress + pDeltaTime * 0.005f, 0.0f, 1.0f);
        const uint8 alpha = mTransitionState == TransitionState::Out
                                ? mStateTransitionProgress * 255
                                : (1.0f - mStateTransitionProgress) * 255;

        SDL_SetRenderDrawColor(mSdlRenderer.get(), 0, 0, 0, alpha);
        SDL_Rect rectangle{0, 0, mRenderDevice.Width, mRenderDevice.Height};
        SDL_RenderFillRect(mSdlRenderer.get(), &rectangle);
    }

    void Engine::RequestStateChange(std::unique_ptr<AbstractStateCreator> pNextStateCreator)
    {
        mNextState = pNextStateCreator->Create(*this);
    }

    bool Engine::GetKeyDown(const SDL_Scancode pScancode) const
    {
        return mKeyboardState[pScancode];
    }

    RenderDevice* Engine::GetRenderDevice()
    {
        return &mRenderDevice;
    }
}
