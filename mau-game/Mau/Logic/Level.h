#ifndef MAU_LEVEL_H
#define MAU_LEVEL_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include <map>
#include <set>
#include <vector>
#include <unordered_map>

#include "Mau/Base/Types.h"
#include "Mau/IO/Resources/Texture.h"

namespace Mau
{
    class AbstractEntityCreator;
    class Engine;
    class Entity;
    class GameplayState;
    class Player;

    enum class Key
    {
        None, Red, Blue, Yellow
    };

    struct Tile
    {
        Tile() = default;
        Tile(bool pBlockRaycast, bool pIsDoor, Texture* pWallTexture, Key pKeyNeeded = Key::None);

        bool BlockRaycast{false};
        bool IsDoor{false};
        Texture* WallTexture{nullptr};
        Key KeyNeeded{ Key::None };

        //defaults
        float DoorClosedPercent{ 1.0f };
        std::set<Entity*> Entities{};
    };

    class Level
    {
    public:
        struct RaycastInfo
        {
            Mau::Vec2f HitPosition;      // World-space hit distance
            float HitPositionPlaneSpace; // For texture coordinates
            Mau::Vec2i TileCoordinate;   // Tile hit by the ray
            Tile* Tile;
            bool HitHorizontalSide;      // True if ray hit horizontal side of the tile.
            std::set<Entity*> Entities;  // Entities touched during ray pass;
        };

        Level(Engine& pEngine, GameplayState& pGameplayState, std::shared_ptr<Texture> pTexture);
        Level(const Level&) = delete;
        Level& operator=(const Level&) = delete;
        ~Level();

        void FixedUpdate(float pFixedDeltaTime);
        void Update(float pDeltaTime);

        void Spawn(std::unique_ptr<Entity> pEntity);

        Player* GetPlayer();

        Tile& GetTile(const Vec2i pCoordinate);

        RaycastInfo RaycastWall(const Mau::Vec2f& rayPosition, const Mau::Vec2f& rayDirection);

    public:
        const int32 Width;
        const int32 Height;
    private:
        Engine& mEngine;
        GameplayState& mGameplayState;
        std::vector<Tile> mTiles;
        std::vector<Vec2i> mDoorCoordinates;
        std::vector<std::unique_ptr<Entity>> mEntities;
        std::vector<std::unique_ptr<Entity>> mEntitySpawnQueue;
        std::unique_ptr<Player> mPlayer{nullptr};
        std::map<std::pair<int32, int32>, std::string> mDialogueTriggers;

        std::unordered_map<uint32, Tile> mRegisteredTiles;
        std::unordered_map<uint32, std::unique_ptr<AbstractEntityCreator>> mRegisteredEntities;
    };
}

#endif MAU_LEVEL_H
