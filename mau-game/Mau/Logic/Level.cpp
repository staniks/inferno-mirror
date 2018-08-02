#include "Mau/Base/Engine.h"
#include "Mau/Logic/Entity.h"
#include "Mau/Logic/Level.h"
#include "Mau/Logic/Player.h"
#include "Mau/Logic/Monsters/Monsters.h"
#include "Mau/Logic/Pickups/PickupWeapons.h"
#include "Pickups/PickupHealth.h"
#include "Pickups/PickupAmmo.h"
#include "Pickups/PickupRelic.h"
#include "Pickups/PickupKeycard.h"
#include "Pickups/PickupExit.h"

using namespace Mau;

namespace Mau
{
    Tile::Tile(bool pBlockRaycast, bool pIsDoor, Texture* pWallTexture, Key pKeyNeeded)
        :
        BlockRaycast(pBlockRaycast),
        IsDoor(pIsDoor),
        WallTexture(pWallTexture),
        KeyNeeded(pKeyNeeded)
    {
    }

    Level::Level(Engine& pEngine, GameplayState& pGameplayState, std::shared_ptr<Texture> pTexture)
        :
        mEngine(pEngine),
        Width(pTexture->GetWidth()),
        Height(pTexture->GetHeight()),
        mGameplayState(pGameplayState)
    {
        // TILES
        mRegisteredTiles[Color{255, 255, 255, 255}.ToUint32()] = Tile{false, false, nullptr};
        mRegisteredTiles[Color{0, 0, 0, 255}.ToUint32()] = Tile{
            true, false, mEngine.TextureCache.GetResource("wall_plain.png").get()
        };
        mRegisteredTiles[Color{0, 45, 0, 255}.ToUint32()] = Tile{
            true, false, mEngine.TextureCache.GetResource("wall_circuits.png").get()
        };
        mRegisteredTiles[Color{0, 64, 0, 255}.ToUint32()] = Tile{
            true, false,
            mEngine.TextureCache.GetResource("wall_logo_1.png").get()
        };
        mRegisteredTiles[Color{128, 128, 128, 255}.ToUint32()] = Tile{
            true, true, mEngine.TextureCache.GetResource("door_active.png").get()
        };
        mRegisteredTiles[Color{64, 64, 64, 255}.ToUint32()] = Tile{
            true, false, mEngine.TextureCache.GetResource("door_interior.png").get()
        };
        mRegisteredTiles[Color{198, 198, 198, 255}.ToUint32()] = Tile{
            true, false, mEngine.TextureCache.GetResource("door_inactive.png").get()
        };
        mRegisteredTiles[Color{255, 128, 128, 255}.ToUint32()] = Tile{
            true, false, mEngine.TextureCache.GetResource("wall_grafiti.png").get()
        };
        mRegisteredTiles[Color{255, 174, 94, 255}.ToUint32()] = Tile{
            true, false, mEngine.TextureCache.GetResource("wall_logo_2.png").get()
        };
        mRegisteredTiles[Color{0, 130, 0, 255}.ToUint32()] = Tile{
            true, false, mEngine.TextureCache.GetResource("wall_logo_3.png").get()
        };

        // Keyed doors
        mRegisteredTiles[Color{145, 85, 85, 255}.ToUint32()] = Tile{
            true, true, mEngine.TextureCache.GetResource("door_red.png").get(), Key::Red
        };
        mRegisteredTiles[Color{99, 108, 142, 255}.ToUint32()] = Tile{
            true, true, mEngine.TextureCache.GetResource("door_blue.png").get(), Key::Blue
        };
        mRegisteredTiles[Color{142, 141, 98, 255}.ToUint32()] = Tile{
            true, true, mEngine.TextureCache.GetResource("door_yellow.png").get(), Key::Yellow
        };

        // Entities
        mRegisteredEntities[Color{255, 0, 0, 255}.ToUint32()] = std::make_unique<EntityCreator<PickupHealth>>();
        mRegisteredEntities[Color{255, 0, 170, 255}.ToUint32()] = std::make_unique<EntityCreator<PickupArmor>>();
        mRegisteredEntities[Color{91, 127, 0, 255}.ToUint32()] = std::make_unique<EntityCreator<PickupAmmoToilet>>();
        mRegisteredEntities[Color{10, 84, 80, 255}.ToUint32()] = std::make_unique<EntityCreator<PickupAmmoPlasma>>();
        mRegisteredEntities[Color{17, 142, 136, 255}.ToUint32()] = std::make_unique<EntityCreator<PickupAmmoRocket>>();
        mRegisteredEntities[Color{127, 0, 0, 255}.ToUint32()] = std::make_unique<EntityCreator<PickupWeaponToilet>>();
        mRegisteredEntities[Color{128, 0, 0, 255}.ToUint32()] = std::make_unique<EntityCreator<PickupWeaponPlasma>>();
        mRegisteredEntities[Color{129, 0, 0, 255}.ToUint32()] = std::make_unique<EntityCreator<PickupWeaponRocket>>();
        mRegisteredEntities[Color{127, 106, 0, 255}.ToUint32()] = std::make_unique<EntityCreator<MonsterLaserPussy>>();
        mRegisteredEntities[Color{127, 51, 0, 255}.ToUint32()] = std::make_unique<EntityCreator<MonsterBall>>();
        mRegisteredEntities[Color{255, 106, 0, 255}.ToUint32()] = std::make_unique<EntityCreator<MonsterShotgunPussy>>();
        mRegisteredEntities[Color{183, 108, 108, 255}.ToUint32()] = std::make_unique<EntityCreator<PickupKeycardRed>>();
        mRegisteredEntities[Color{141, 147, 181, 255}.ToUint32()] = std::make_unique<EntityCreator<PickupKeycardBlue>>();
        mRegisteredEntities[Color{181, 170, 126, 255}.ToUint32()] = std::make_unique<EntityCreator<PickupKeycardYellow>>();
        mRegisteredEntities[Color{ 224, 224, 224, 255 }.ToUint32()] = std::make_unique<EntityCreator<PickupExit>>();

        mTiles.resize(Width * Height);

        LexData triggerLexData{RESOURCE_DIRECTORY_PREFIX + std::string("dialogue_triggers.mau")};

        auto triggerIterator = triggerLexData.GetIterator();
        while (triggerIterator != triggerLexData.GetLexems().end())
        {
            const int32 x = std::stoi(*triggerIterator);
            ++triggerIterator;
            const int32 y = std::stoi(*triggerIterator);
            ++triggerIterator;
            const std::string dialogueName = *triggerIterator;
            ++triggerIterator;

            mDialogueTriggers[{x, y}] = dialogueName;
        }

        // FIRST PASS - World
        for (int y = 0; y < Height; ++y)
        {
            for (int x = 0; x < Width; ++x)
            {
                auto pixelColor = pTexture->GetPixelColor({x, y}).ToUint32();
                const auto it = mRegisteredTiles.find(pixelColor);

                if (it != mRegisteredTiles.end())
                {
                    mTiles[y * Width + x] = it->second;
                    if (it->second.IsDoor)
                    {
                        mDoorCoordinates.emplace_back(x, y);
                    }
                }
                else
                {
                    // in case there's an item here, assume there's only the floor
                    mTiles[y * Width + x] = mRegisteredTiles[Color{255, 255, 255, 255}.ToUint32()];
                }
            }
        }

        // SECOND PASS - Entities
        for (int y = 0; y < Height; ++y)
        {
            for (int x = 0; x < Width; ++x)
            {
                auto pixelColor = pTexture->GetPixelColor({x, y}).ToUint32();

                // if player
                if (pixelColor == Color{0, 255, 0, 255}.ToUint32())
                {
                    if (mPlayer != nullptr)
                    {
                        continue;
                    }
                    mPlayer = std::make_unique<Player>(mGameplayState, *this, Vec2f{x + 0.5f, y + 0.5f});
                }
                else
                {
                    const auto it = mRegisteredEntities.find(pixelColor);

                    if (it != mRegisteredEntities.end())
                    {
                        mEntities.push_back(
                            mRegisteredEntities[pixelColor]->Create(mGameplayState, *this, Vec2f{x + 0.5f, y + 0.5f}));
                    }
                }
            }
        }

        // THIRD PASS - Relics
        LexData relicLexData{RESOURCE_DIRECTORY_PREFIX + std::string("relics.mau")}; //todo: directory prefix is error prone, refactor this

        auto relicIterator = relicLexData.GetIterator();
        while (relicIterator != relicLexData.GetLexems().end())
        {
            const int32 x = std::stoi(*relicIterator);
            ++relicIterator;
            const int32 y = std::stoi(*relicIterator);
            ++relicIterator;
            const std::string relicName = *relicIterator;
            ++relicIterator;
            const std::string dialogueName = *relicIterator;
            ++relicIterator;

            mEntities.push_back(std::make_unique<PickupRelic>(mGameplayState, *this, Vec2f{x + 0.5f, y + 0.5f},
                                                              relicName, dialogueName));
        }
    }

    Level::~Level()
    {
    }

    void Level::FixedUpdate(float pFixedDeltaTime)
    {
        mPlayer->FixedUpdate(pFixedDeltaTime);

        for (auto& entity : mEntities)
        {
            if (!entity->IsMarkedForDestruction())
            {
                entity->FixedUpdate(pFixedDeltaTime);
            }
        }

        // Another pass is needed because we would be invalidating iterators while spawning entities
        // from FixedUpdate.
        for (auto& entity : mEntitySpawnQueue)
        {
            mEntities.emplace_back(std::move(entity));
        }
        mEntitySpawnQueue.clear();

        for (const Vec2i& coordinates : mDoorCoordinates)
        {
            Tile& tile = GetTile(coordinates);
            bool shouldBeOpen = false;

            for (const auto& entity : GetTile(coordinates).Entities)
            {
                if (entity == GetPlayer() || (entity->GetType() == EntityType::Monster && !dynamic_cast<Monster*>(entity)->IsDead()))
                {
                    if (tile.KeyNeeded != Key::None && entity != GetPlayer())
                    {
                        // Monsters can't open keyed doors
                        continue;
                    }

                    if (entity == GetPlayer() && tile.KeyNeeded != Key::None)
                    {
                        if (!dynamic_cast<Player*>(entity)->HasKey(tile.KeyNeeded))
                            continue;
                    }

                    const float distance = (entity->GetPosition() - Vec2f{coordinates.x + 0.5f, coordinates.y + 0.5f}).
                        Length();

                    if (distance < 2.0f)
                    {
                        shouldBeOpen = true;
                        break;
                    }
                }
            }

            if (shouldBeOpen)
            {
                tile.DoorClosedPercent -= pFixedDeltaTime / 200.0f;
            }
            else
            {
                tile.DoorClosedPercent += pFixedDeltaTime / 200.0f;
            }

            tile.DoorClosedPercent = Clamp(tile.DoorClosedPercent, 0.0f, 1.0f);
        }
    }

    void Level::Update(float pDeltaTime)
    {
        mPlayer->Update(pDeltaTime);

        std::vector<std::unique_ptr<Entity>>::iterator iterator = mEntities.begin();
        while (iterator != mEntities.end())
        {
            if ((*iterator)->IsMarkedForDestruction())
            {
                iterator = mEntities.erase(iterator);
            }
            else
            {
                (*iterator)->Update(pDeltaTime);
                ++iterator;
            }
        }

        auto dialogueTriggerIterator = mDialogueTriggers.begin();
        while (dialogueTriggerIterator != mDialogueTriggers.end())
        {
            if (std::make_pair<int32, int32>(mPlayer->GetPosition().x, mPlayer->GetPosition().y) ==
                dialogueTriggerIterator->first)
            {
                mGameplayState.QueueDialogue(dialogueTriggerIterator->second, 0.0f);
                dialogueTriggerIterator = mDialogueTriggers.erase(dialogueTriggerIterator);
            }
            else
            {
                ++dialogueTriggerIterator;
            }
        }
    }

    void Level::Spawn(std::unique_ptr<Entity> pEntity)
    {
        mEntitySpawnQueue.emplace_back(std::move(pEntity));
    }

    Player* Level::GetPlayer()
    {
        return mPlayer.get();
    }

    Tile& Level::GetTile(const Vec2i pCoordinate)
    {
        return mTiles[pCoordinate.y * Width + pCoordinate.x];
    }

    Level::RaycastInfo Level::RaycastWall(const Mau::Vec2f& rayPosition, const Mau::Vec2f& rayDirection)
    {        
        Vec2i cellPosition{ static_cast<int32>(rayPosition.x),  static_cast<int32>(rayPosition.y) };
        Vec2f worldPosition = rayPosition;

        const Vec2f deltaDistance{ std::abs(1 / rayDirection.x) , std::abs(1 / rayDirection.y) };

        bool rayHitWall{ false };
        bool rayHitHorizontalSide = false;

        std::set<Entity*> entitySet;

        Tile& startingTile = GetTile({ cellPosition.x, cellPosition.y});
        entitySet.insert(startingTile.Entities.begin(), startingTile.Entities.end());
                
        while (!rayHitWall)
        {            
            Vec2f sideDistance{};
            Vec2i stepDirection{};

            if (rayDirection.x < 0)
            {
                sideDistance.x = (worldPosition.x - cellPosition.x) * deltaDistance.x;
                stepDirection.x = -1;
            }
            else
            {
                sideDistance.x = (cellPosition.x + 1.0 - worldPosition.x) * deltaDistance.x;
                stepDirection.x = 1;
            }

            if (rayDirection.y < 0)
            {
                sideDistance.y = (worldPosition.y - cellPosition.y) * deltaDistance.y;
                stepDirection.y = -1;
            }
            else
            {
                sideDistance.y = (cellPosition.y + 1.0 - worldPosition.y) * deltaDistance.y;
                stepDirection.y = 1;
            }
                        
            if (sideDistance.x < sideDistance.y)
            {
                worldPosition += rayDirection * sideDistance.x;
                cellPosition.x += stepDirection.x;
                rayHitHorizontalSide = true;
            }
            else
            {
                worldPosition += rayDirection * sideDistance.y;
                cellPosition.y += stepDirection.y;
                rayHitHorizontalSide = false;
            }

            Tile& currentTile = GetTile({ cellPosition.x, cellPosition .y});

            if (currentTile.IsDoor)
            {
                const float planeSpaceHitPosition = rayHitHorizontalSide
                                                        ? std::abs(worldPosition.y - cellPosition.y)
                                                        : std::abs(worldPosition.x - cellPosition.x);
                if (planeSpaceHitPosition >= currentTile.DoorClosedPercent / 2.0f && 
                    planeSpaceHitPosition <= 1.0f - currentTile.DoorClosedPercent / 2.0f)
                {
                    continue;
                }
            }
            
            if (currentTile.BlockRaycast)
            {
                rayHitWall = true;
            }
            else
            {
                entitySet.insert(currentTile.Entities.begin(), currentTile.Entities.end());
            }
        }

        Tile& hitTile = GetTile({ cellPosition.x, cellPosition.y});

        RaycastInfo info;
        info.HitPosition = worldPosition;

        if (rayHitHorizontalSide)
        {
            info.HitPositionPlaneSpace = std::abs(worldPosition.y - cellPosition.y);
            if (worldPosition.x > cellPosition.x)
            {
                info.HitPositionPlaneSpace = 1.0f - info.HitPositionPlaneSpace;
            }
        }
        else
        {
            info.HitPositionPlaneSpace = 1.0f - std::abs(worldPosition.x - cellPosition.x);
            if (worldPosition.y > cellPosition.y)
            {
                info.HitPositionPlaneSpace = 1.0f - info.HitPositionPlaneSpace;
            }
        }

        if (hitTile.IsDoor)
        {
            if (info.HitPositionPlaneSpace < 0.5f)
            {
                info.HitPositionPlaneSpace += (1.0f - hitTile.DoorClosedPercent) / 2;                
            }
            else
            {
                info.HitPositionPlaneSpace -= (1.0f - hitTile.DoorClosedPercent) / 2;                
            }
        }

        info.TileCoordinate = { cellPosition.x, cellPosition .y};
        info.Tile = &hitTile;
        info.HitHorizontalSide = rayHitHorizontalSide;
        info.Entities = entitySet;

        return info;
    }
}
