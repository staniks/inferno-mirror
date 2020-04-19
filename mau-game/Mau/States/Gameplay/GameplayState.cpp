#include <cstdio>

#include "Mau/Logic/Player.h"
#include "Mau/States/Gameplay/GameplayState.h"
#include "Mau/States/Gameplay/Substates/DialogueState.h"
#include "Mau/States/Gameplay/Substates/QuitPromptState.h"
#include "Mau/States/Story/Substates/DeadState.h"

//#define DISABLE_DIALOGUE

#ifdef USE_SPRINTF_S
#define sprintf sprintf_s
#endif

namespace Mau
{
    GameplayState::GameplayState(Engine& pEngine)
        :
        State(pEngine),
        DialogueRepository(RESOURCE_DIRECTORY_PREFIX + std::string("dialogue.mau"), mEngine.TextureCache),
        mLevel(pEngine, *this, pEngine.TextureCache.GetResource("level.png")),
        mGuiKeyRed(pEngine.TextureCache.GetResource("gui_key_red.png")),
        mGuiKeyBlue(pEngine.TextureCache.GetResource("gui_key_blue.png")),
        mGuiKeyYellow(pEngine.TextureCache.GetResource("gui_key_yellow.png"))
    {
        InitializeHorizontalLookupTables();
    }

    void GameplayState::HandleEvent(SDL_Event* pEvent)
    {
        if (pEvent->type == SDL_KEYDOWN && pEvent->key.keysym.sym == SDLK_ESCAPE)
        {
            PushSubstate(std::make_unique<QuitPromptState>(mEngine, *this));
        }

        if (mSubstateStack.empty())
        {
            if (pEvent->type == SDL_KEYDOWN)
            {
                switch (pEvent->key.keysym.sym)
                {
                case SDLK_LCTRL: break;
                default: break;
                }
            }
        }
        else
        {
            mSubstateStack.back()->HandleEvent(pEvent);
        }
    }

    void GameplayState::FixedUpdate(float pFixedDeltaTime)
    {
        if (mSubstateStack.empty())
        {
            mLevel.FixedUpdate(pFixedDeltaTime);
        }
        else
        {
            mSubstateStack.back()->FixedUpdate(pFixedDeltaTime);
        }
    }

    void GameplayState::Update(float pDeltaTime)
    {
        if (mSubstateStack.empty())
        {
            Player* player = mLevel.GetPlayer();

            Vec2f desiredVelocity{};

            mCurrentMessageTimer -= pDeltaTime / 1000.0f;
            if (mCurrentMessageTimer < 0)
            {
                mCurrentMessageTimer = 0;
            }

            mFlashTimer -= pDeltaTime / 1000.0f;
            if (mFlashTimer < 0.0f)
            {
                mFlashTimer = 0;
            }

            if (mEngine.GetKeyDown(SDL_SCANCODE_RIGHT))
            {
                player->Rotate(pDeltaTime / 400.0f); // todo: get rid of magic number
            }
            if (mEngine.GetKeyDown(SDL_SCANCODE_LEFT))
            {
                player->Rotate(-pDeltaTime / 400.0f); // todo: get rid of magic number
            }
            if (mEngine.GetKeyDown(SDL_SCANCODE_UP) || mEngine.GetKeyDown(SDL_SCANCODE_W))
            {
                desiredVelocity += player->GetDirection();
            }
            if (mEngine.GetKeyDown(SDL_SCANCODE_DOWN) || mEngine.GetKeyDown(SDL_SCANCODE_S))
            {
                desiredVelocity += player->GetDirection() * (-1.0f);
            }
            if (mEngine.GetKeyDown(SDL_SCANCODE_A))
            {
                desiredVelocity += player->GetRight() * (-1.0f);
            }
            if (mEngine.GetKeyDown(SDL_SCANCODE_D))
            {
                desiredVelocity += player->GetRight();
            }
            if (mEngine.GetKeyDown(SDL_SCANCODE_LCTRL) || (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(
                SDL_BUTTON_LEFT)))
            {
                player->Fire();
            }
            if (mEngine.GetKeyDown(SDL_SCANCODE_1))
            {
                player->SwitchWeapon(0);
            }
            if (mEngine.GetKeyDown(SDL_SCANCODE_2))
            {
                player->SwitchWeapon(1);
            }
            if (mEngine.GetKeyDown(SDL_SCANCODE_3))
            {
                player->SwitchWeapon(2);
            }

            player->Rotate(mEngine.MouseDeltaX / 256.0f); // todo: get rid of magic number

            if (desiredVelocity.Length() > 0)
            {
                desiredVelocity.Normalize();
                player->SetVelocity(desiredVelocity / 300.0f); // todo: get rid of magic number
            }

            // todo: get rid of magic numbers:
            float speed = player->GetVelocity().Length() / (1.0f / 300.0f);
            mCurrentWeaponBob = std::remainder(mCurrentWeaponBob + pDeltaTime * speed / 1500.0f, DoublePI);

            mLevel.Update(pDeltaTime);

            // Decrement delayed dialogue timers
            auto iterator = mDelayedDialogue.begin();
            while (iterator != mDelayedDialogue.end())
            {
                if ((*iterator).second <= 0.0f)
                {
                    PushSubstate(std::make_unique<DialogueState>(mEngine, *this, (*iterator).first));
                    mDelayedDialogue.erase(iterator);
                    break;
                }
                else
                {
                    (*iterator).second -= pDeltaTime / 1000.0f;
                    ++iterator;
                }
            }

            if (player->GetHealth() <= 0)
            {
                mEngine.RequestStateChange(std::make_unique<StateCreator<DeadState>>());
            }
        }
        else
        {
            mSubstateStack.back()->Update(pDeltaTime);
        }


    }

    void GameplayState::Render(float pDeltaTime)
    {
        const auto renderDevice = mEngine.GetRenderDevice();

        const auto wallTexture = mEngine.TextureCache.GetResource("test2.png").get();
        const auto hudFrameTexture = mEngine.TextureCache.GetResource("HUDFrame.png").get();
        const auto weaponTexture = mEngine.TextureCache.GetResource("weapon_toilet.png").get();

        const auto font = mEngine.FontCache.GetResource("font_red.mau").get();
        const auto fontSmall = mEngine.FontCache.GetResource("font_small_red.mau").get();

        RenderWorld();

        if (mFlashTimer > 0)
        {
            renderDevice->RenderFill(Color{
                mFlashColor.r, mFlashColor.g, mFlashColor.b,
                static_cast<byte>(mFlashColor.a * mFlashTimer / mFlashDuration)
            });
        }

        const int32 weaponPosX = std::sinf(mCurrentWeaponBob * 10.0f) * 8;
        const int32 weaponPosY = std::abs(std::cosf(mCurrentWeaponBob * 10.0f)) * 8 + renderDevice->Height -
            weaponTexture->
            GetHeight();

        Player* player = mLevel.GetPlayer();

        Weapon* currentWeapon = player->GetCurrentWeapon();

        if (currentWeapon)
        {
            const Vec2i recoilOffset = Vec2i{12, 16} * player->GetWeaponRecoilProgress();

            renderDevice->RenderTexture(currentWeapon->GetTexture(), Vec2i{
                weaponPosX, weaponPosY + static_cast<int32>(player->GetWeaponSwitchProgress() * 64)
            } + recoilOffset);

            Texture* crosshairTexture = currentWeapon->CrosshairTexture.get();

            const Vec2i crosshairCoordinates = Vec2i{
                mEngine.GetRenderDevice()->Width / 2, mEngine.GetRenderDevice()->Height / 2
            } - Vec2i{crosshairTexture->GetWidth() / 2, crosshairTexture->GetHeight() / 2};
            renderDevice->RenderTexture(currentWeapon->CrosshairTexture.get(), crosshairCoordinates);
        }

        renderDevice->RenderTexture(hudFrameTexture, {0, renderDevice->Height - hudFrameTexture->GetHeight()});

        // Render keys
        const int32 guiKeyX = 233;
        const int32 guiKeyY = renderDevice->Height - hudFrameTexture->GetHeight() + 20;
        if(player->HasKey(Key::Red))
        {
            renderDevice->RenderTexture(mGuiKeyRed.get(), { guiKeyX, guiKeyY });
        }
        if (player->HasKey(Key::Blue))
        {
            renderDevice->RenderTexture(mGuiKeyBlue.get(), { guiKeyX + mGuiKeyRed->GetWidth() + 1, guiKeyY });
        }
        if (player->HasKey(Key::Yellow))
        {
            renderDevice->RenderTexture(mGuiKeyYellow.get(), { guiKeyX + (mGuiKeyRed->GetWidth() + 1) * 2, guiKeyY });
        }

        // Render stats
        char buffer[] = "0000";
        if (currentWeapon)
        {
            sprintf(buffer, "%04d", currentWeapon->GetAmmo());
        }
        renderDevice->RenderString(font, {62, 174}, buffer);

        sprintf(buffer, "%03d%%", player->GetHealth());
        renderDevice->RenderString(font, {107, 174}, buffer);

        sprintf(buffer, "%03d%%", player->GetArmor());
        renderDevice->RenderString(font, {182, 174}, buffer);

        // Render message
        if (mCurrentMessageTimer > 0)
        {
            // Render overlay
            for (int y = 0; y < fontSmall->CharacterSize.y; ++y)
            {
                for (int x = 0; x < renderDevice->Width; ++x)
                {
                    const float intensity = 1.0f - static_cast<float>(x) / renderDevice->Width;
                    renderDevice->RenderPixelAlphaBlend({ x, y }, { 0, 0, 0, static_cast<byte>(128 * intensity) });
                }
            }

            renderDevice->RenderString(fontSmall, {0, 0}, mCurrentMessage);

        }

        for (auto& state : mSubstateStack)
        {
            state->Render(pDeltaTime);
        }
    }

    void GameplayState::DisplayMessage(const std::string& pMessage)
    {
        mCurrentMessage = pMessage;
        mCurrentMessageTimer = 4.0f;
    }

    void GameplayState::FlashScreen(const Color& pColor)
    {
        mFlashColor = pColor;
        mFlashTimer = mFlashDuration;
    }

    void GameplayState::PushSubstate(std::unique_ptr<GameplaySubstate> pSubstate)
    {
#ifndef DISABLE_DIALOGUE
        mSubstateStack.push_back(std::move(pSubstate));
#endif
    }

    void GameplayState::PopSubstate()
    {
        mSubstateStack.pop_back();
    }

    void GameplayState::QueueDialogue(std::string pDialogueId, float pTime)
    {
        mDelayedDialogue.emplace_back(std::make_pair(pDialogueId, pTime));
    }

    void GameplayState::InitializeHorizontalLookupTables()
    {
        /* Since we're emulating wolf3d style, we're using solid colors instead of textures for floor and ceiling. However, added light attenuation (fog) for eye candy. */

        const Color floorColor{36 / 2, 52 / 2, 64 / 2, 255};
        const Color ceilingColor{36 / 4, 52 / 4, 64 / 4, 255};

        mHorizontalLookupTable.resize(mEngine.GetRenderDevice()->Height);
        for (auto y = 0; y < mEngine.GetRenderDevice()->Height; ++y)
        {
            const float worldSpaceDivisor = (y >= mEngine.GetRenderDevice()->Height / 2)
                                                ? (2.0f * y - mEngine.GetRenderDevice()->Height)
                                                : (mEngine.GetRenderDevice()->Height - 2.0f * y);

            const float worldSpaceZ = mEngine.GetRenderDevice()->Height / worldSpaceDivisor;

            Color color = (y >= mEngine.GetRenderDevice()->Height / 2) ? floorColor : ceilingColor;

            const float fogFactor = worldSpaceZ / mFogReductionFactor;
            const float fogAmount = fogFactor >= 1.0f ? fogFactor : 1.0f;

            color.r /= fogAmount;
            color.g /= fogAmount;
            color.b /= fogAmount;

            mHorizontalLookupTable[y] = color;
        }
    }

    void GameplayState::RenderWorld()
    {
        const auto renderDevice = mEngine.GetRenderDevice();
        Player* player = mLevel.GetPlayer();

        std::vector<float> depthBuffer(mEngine.GetRenderDevice()->Width);

        // Focal length is used to determine the angle at which the rays are cast
        const float cameraFocalLength = mEngine.GetRenderDevice()->Width / (2 * std::tanf(player->FieldOfView / 2.0f));

        // Half of the vertical field of view. It is used for perspective projection of screen columns.
        const float halfVerticalFov = (static_cast<float>(mEngine.GetRenderDevice()->Height) / mEngine
                                                                                               .GetRenderDevice()->Width
        ) * player->FieldOfView / 2.0f;

        // Half field of views
        const float tanHalfHorizontalFov = std::tanf(player->FieldOfView / 2);
        const float tanHalfVerticalFov = std::tanf(halfVerticalFov);

        // Visible entities (the ones touched by rays)
        std::set<Entity*> entitySet;

        // Render the projected map
        for (auto column = 0; column < renderDevice->Width; ++column)
        {
            // Calculate the angle at which the ray is cast from the camera
            const auto screenSpaceAngle = std::atanf((column - renderDevice->Width / 2) / cameraFocalLength);
            const auto worldSpaceAngle = player->GetRotation() + screenSpaceAngle;

            // Cast a ray and determine an intersection point
            const Vec2f rayDirection{std::cosf(worldSpaceAngle), std::sinf(worldSpaceAngle)};
            const auto raycastInfo = mLevel.RaycastWall(player->GetPosition(), rayDirection);

            // Fill the entity set with visible entities
            entitySet.insert(raycastInfo.Entities.begin(), raycastInfo.Entities.end());

            // Calculate the world-space distance from the camera to the intersection point
            const auto hitDistance = (raycastInfo.HitPosition - player->GetPosition()).Length();

            // Screen-space Z (to avoid fisheye effect)
            const auto z = hitDistance * std::cosf(screenSpaceAngle);

            // We store screen-space depth in depth buffer for simplicity
            depthBuffer[column] = z;

            // Project the column to screen space
            const int32 columnHeight = renderDevice->Height / (2 * z * tanHalfVerticalFov);

            if (columnHeight == 0) //prevent division by zero
                continue;

            auto columnStartY = renderDevice->Height / 2 - columnHeight / 2;
            auto columnEndY = columnStartY + columnHeight;

            // Clamp the column height in screen-space.
            if (columnStartY < 0)
            {
                columnStartY = 0;
            }
            if (columnEndY > renderDevice->Height - 1)
            {
                columnEndY = renderDevice->Height - 1;
            }

            // Render the ceiling (if visible)
            for (auto y = 0; y < columnStartY; ++y)
            {
                renderDevice->RenderPixel({column, y}, mHorizontalLookupTable[y]);
            }

            Texture* wallTexture = raycastInfo.Tile->WallTexture;

            // Cache things before rendering the wall
            const int32 columnScreenHeightDelta = columnHeight - renderDevice->Height;
            const int32 doubleColumnHeight = 2 * columnHeight;
            const int32 textureX = static_cast<int32>(raycastInfo.HitPositionPlaneSpace * wallTexture->
                GetWidth());

            const float fogFactor = hitDistance / mFogReductionFactor;
            const auto fogAmount = fogFactor >= 1.0f ? fogFactor : 1.0f;

            // Render the wall
            for (auto y = columnStartY; y < columnEndY; ++y)
            {
                const int32 d = y * 2 + columnScreenHeightDelta;
                const int32 textureY = d * wallTexture->GetHeight() / doubleColumnHeight;

                auto color = wallTexture->GetPixelColor({textureX, textureY});

                if (!raycastInfo.HitHorizontalSide)
                {
                    color.r >>= 1;
                    color.g >>= 1;
                    color.b >>= 1;
                }

                color.r /= fogAmount;
                color.g /= fogAmount;
                color.b /= fogAmount;

                renderDevice->RenderPixel({column, y}, color);
            }

            // Render the floor (if visible)
            for (auto y = columnEndY; y < renderDevice->Height; ++y)
            {
                renderDevice->RenderPixel({column, y}, mHorizontalLookupTable[y]);
            }
        }

        // Sort the entities in relation to camera
        std::vector<Entity*> sortedEntities;

        // Poor man's insertion sort based on distance
        for (Entity* entity : entitySet)
        {
            if (sortedEntities.empty())
            {
                sortedEntities.push_back(entity);
            }
            else
            {
                const float entityDistance = (entity->GetPosition() - player->GetPosition()).Length();

                std::vector<Entity*>::iterator it;
                for (it = sortedEntities.begin(); it != sortedEntities.end(); ++it)
                {
                    Entity* sortedEntity = *it;
                    const float sortedEntityDistance = (sortedEntity->GetPosition() - player->GetPosition()).Length();

                    if (entityDistance > sortedEntityDistance)
                    {
                        sortedEntities.insert(it, entity);
                        break;
                    }
                }

                if (it == sortedEntities.end())
                {
                    sortedEntities.push_back(entity);
                }
            }
        }

        // Render visible entities sorted back to front
        for (Entity* entity : sortedEntities)
        {
            if (entity == player)
                continue;

            const auto entityTexture = entity->GetCurrentTexture();

            if (!entityTexture) continue;

            // Calculate the difference vector between entity and the camera
            const Vec2f differenceVector = entity->GetPosition() - player->GetPosition();
            const Vec2f cameraDirection = player->GetDirection();

            // The dot product and determinant are used to calculate screen space angle
            const float dot = Vec2f::Dot(cameraDirection, differenceVector);
            const float det = Vec2f::Det(cameraDirection, differenceVector);

            // Calculate the screen-space angle at which the entity is projected
            const float screenSpaceAngle = std::atan2(det, dot);


            // Calculate the world-space distance from the camera to the entity center
            const auto hitDistance = differenceVector.Length();

            // Screen-space Z (to avoid fisheye effect)
            const auto z = hitDistance * std::cosf(screenSpaceAngle);

            // Project the entity to screen space
            const int32 entityHeight = renderDevice->Height / (2 * z * tanHalfVerticalFov);
            const int32 entityWidth = renderDevice->Width / (2 * z * tanHalfHorizontalFov);

            auto columnStartY = renderDevice->Height / 2 - entityHeight / 2 + static_cast<int>(entity->VerticalOffset);
            auto columnEndY = columnStartY + entityHeight + static_cast<int>(entity->VerticalOffset);

            // Clamp the column height in screen-space.
            if (columnStartY < 0)
            {
                columnStartY = 0;
            }
            if (columnEndY > renderDevice->Height - 1)
            {
                columnEndY = renderDevice->Height - 1;
            }

            // Calculate screen space X
            const int32 screenSpaceX = cameraFocalLength * std::tan(screenSpaceAngle) + renderDevice->Width / 2;

            const int32 entityStartX = screenSpaceX - entityWidth / 2;
            const int32 entityEndX = screenSpaceX + entityWidth / 2;

            const int32 entityScreenHeightDelta = entityHeight - renderDevice->Height;
            const int32 doubleEntityHeight = 2 * entityHeight;

            for (auto x = entityStartX; x < entityEndX; ++x)
            {
                if (x < 0 || x >= renderDevice->Width) continue;

                // Test vertical stripe against Z-buffer and render
                if (depthBuffer[x] > z)
                {
                    const int32 textureX = (static_cast<float>(x - entityStartX) / entityWidth) * entityTexture->
                        GetWidth();

                    const float fogFactor = hitDistance / mFogReductionFactor;
                    const auto fogAmount = fogFactor >= 1.0f ? fogFactor : 1.0f;

                    // Render the sprite vertical stripe
                    for (auto y = columnStartY; y < columnEndY; ++y)
                    {
                        const int32 d = (y) * 2 + entityScreenHeightDelta - static_cast<int>(entity->VerticalOffset);
                        const int32 textureY = d * entityTexture->GetHeight() / doubleEntityHeight;

                        auto color = entityTexture->GetPixelColor({textureX, textureY});

                        color.r /= fogAmount;
                        color.g /= fogAmount;
                        color.b /= fogAmount;

                        renderDevice->RenderPixelAlphaBlend({x, y}, color);
                    }
                }
            }
        }
    }

    GameplaySubstate::GameplaySubstate(Engine& pEngine, GameplayState& pGameplayState)
        :
        State(pEngine),
        mGameplayState(pGameplayState)
    {
    }
}
