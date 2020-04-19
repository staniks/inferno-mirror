#ifndef MAU_ENTITY_H
#define MAU_ENTITY_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include <list>

#include "Mau/Base/Types.h"
#include "Mau/IO/Resources/Texture.h"

namespace Mau
{
    class GameplayState;
    class Level;
    struct Tile;

    enum class EntityType
    {
        Monster,
        Pickup,
        Projectile,
        Particle,
        Player
    };

    class Entity
    {
    public:
        Entity(GameplayState& pGameplayState, Level& pLevel, EntityType pType, Mau::Vec2f pPosition, Vec2f pSize,
               bool pBlocking, bool pIgnoreBlocking);
        virtual ~Entity();

        virtual void FixedUpdate(float pFixedDeltaTime);
        virtual void Update(float pDeltaTime);

        void Move(const Mau::Vec2f pDeltaPosition);
        void Rotate(const float pDeltaRotation);

        void SetPosition(const Mau::Vec2f pPosition);
        void SetVelocity(const Vec2f pVelocity);
        void SetRotation(const float pRotation);

        void Destroy();

        EntityType GetType() const;
        Vec2f GetPosition() const;
        float GetRotation() const;
        Vec2f GetDirection() const;
        Vec2f GetRight() const;
        Vec2f GetSize() const;
        Vec2f GetVelocity() const;
        bool IsBlocking() const;
        bool IsMarkedForDestruction() const;

        virtual Texture* GetCurrentTexture() const { return nullptr; }

        virtual void OnEntityCollision(Entity* pEntity) = 0;
        virtual void OnWallCollision();

    public:
        float VerticalOffset{0};

    private:
        void SetOccupiedTiles();
        void ResetOccupiedTiles();

    private:
        bool mMarkedForDestruction{ false };
        Vec2f mSize;
        float mRotation{ 0 };
        Vec2f mVelocity{ 0, 0 };
        std::list<Tile*> mOccupiedTiles;

    protected:
        GameplayState& mGameplayState;
        Level& mLevel;
        EntityType mType;
        Vec2f mPosition;
        
        bool mBlocking;       
        bool mIgnoreBlocking;
        float mFriction{0.15f};        
    };

    class AbstractEntityCreator
    {
    public:
        virtual ~AbstractEntityCreator() = default;

        virtual std::unique_ptr<Entity> Create(GameplayState& pGameplayState, Level& pLevel, Vec2f pPosition) const = 0;
    };  
    
    template <class T>
    class EntityCreator : public AbstractEntityCreator
    {
    public:
        std::unique_ptr<Entity> Create(GameplayState& pGameplayState, Level& pLevel, Vec2f pPosition) const override
        {
            return std::make_unique<T>(pGameplayState, pLevel, pPosition);
        }
    };
}

#endif MAU_ENTITY_H
