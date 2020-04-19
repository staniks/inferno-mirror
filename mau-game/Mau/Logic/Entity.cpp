#include <algorithm>

#include "Mau/Logic/Entity.h"
#include "Mau/Logic/Level.h"
#include "Mau/Math/Rect.h"
#include "Mau/Math/Math.h"

#define SPATIAL_PARTITIONING_SIZE 1

namespace Mau
{
    Entity::Entity(GameplayState& pGameplayState, Level& pLevel, EntityType pType, Vec2f pPosition, Vec2f pSize, bool pBlocking, bool pIgnoreBlocking)
        :
        mGameplayState(pGameplayState),
        mLevel(pLevel),
        mType(pType),
        mPosition(pPosition),
        mSize(pSize),
        mBlocking(pBlocking),
        mIgnoreBlocking(pIgnoreBlocking)
    {
        SetPosition(mPosition);
    }

    Entity::~Entity()
    {
        ResetOccupiedTiles();
    }

    void Entity::FixedUpdate(float pFixedDeltaTime)
    {
        Move(mVelocity * pFixedDeltaTime);

        mVelocity -= mVelocity * mFriction ;
    }

    void Entity::Update(float pDeltaTime)
    {
    }

    void Entity::Move(const Mau::Vec2f pDeltaPosition)
    {
        std::set<Entity*> collidedWithAlready;
        bool collidedWithWallAlready{ false };

        for(int32 pass = 0; pass < 2; ++pass)
        {
            const Vec2f passDeltaPosition = pass ? Vec2f{pDeltaPosition.x, 0} : Vec2f{0, pDeltaPosition.y};
            
            SetPosition(mPosition + passDeltaPosition);

            // Poor man's spatial partitioning
            const Vec2i minBounds
            {
                std::max(0, static_cast<int32>(mPosition.x) - SPATIAL_PARTITIONING_SIZE),
                std::max(0, static_cast<int32>(mPosition.y) - SPATIAL_PARTITIONING_SIZE),
            };
            const Vec2i maxBounds
            {
                std::min(mLevel.Width - 1, static_cast<int32>(mPosition.x) + SPATIAL_PARTITIONING_SIZE),
                std::min(mLevel.Height - 1, static_cast<int32>(mPosition.y) + SPATIAL_PARTITIONING_SIZE),
            };

            bool collision = false;

            const Rect selfRect{
                mPosition, mSize
            };

            for (int32 y = minBounds.y; y <= maxBounds.y; ++y)
            {
                for (int32 x = minBounds.x; x <= maxBounds.x; ++x)
                {
                    Tile& tile = mLevel.GetTile({ x, y });
                    // Test walls first
                    if (tile.BlockRaycast)
                    {                    
                        if(!(tile.IsDoor && tile.DoorClosedPercent == 0.0f))
                        {
                            const Rect wallRect{
                                Vec2f{ x + 0.5f, y + 0.5f }, Vec2f{ 1, 1 }
                            };

                            if (Rect::Intersects(selfRect, wallRect))
                            {
                                collision = true;
                                if(!collidedWithWallAlready)
                                {
                                    OnWallCollision();
                                    collidedWithWallAlready = true;
                                }
                                break;
                            }
                        }                        
                    }

                    // Test entity collisions
                    for(Entity* entity : mLevel.GetTile({x, y}).Entities)
                    {
                        if (entity == this) continue;                        

                        if (entity->IsMarkedForDestruction() || this->IsMarkedForDestruction())
                            continue;

                        const Rect entityRect{
                            entity->GetPosition(), entity->GetSize()
                        };

                        if (Rect::Intersects(selfRect, entityRect))
                        {
                            if(collidedWithAlready.count(entity) > 0)
                            {
                                continue;
                            }
                            collidedWithAlready.insert(entity);
                            this->OnEntityCollision(entity);
                            entity->OnEntityCollision(this);
                            if(entity->IsBlocking() && !this->mIgnoreBlocking)
                            {
                                collision = true;
                                break;
                            }                             
                        }
                    }
                }

                if (collision) 
                    break;
            }

            if (collision)
            {
                SetPosition(mPosition - passDeltaPosition);                
            }
        }        
    }

    void Entity::Rotate(const float pDeltaRotation)
    {
        SetRotation(mRotation + pDeltaRotation);
    }

    void Entity::SetPosition(const Vec2f pPosition)
    {
        ResetOccupiedTiles();
        mPosition = pPosition;
        SetOccupiedTiles();
    }

    void Entity::SetVelocity(const Vec2f pVelocity)
    {
        mVelocity = pVelocity;
    }

    void Entity::SetRotation(const float pRotation)
    {
        mRotation = std::remainderf(pRotation, DoublePI);
    }

    void Entity::Destroy()
    {
        mMarkedForDestruction = true;
    }

    EntityType Entity::GetType() const
    {
        return mType;
    }

    Vec2f Entity::GetPosition() const
    {
        return mPosition;
    }

    float Entity::GetRotation() const
    {
        return mRotation;
    }

    Mau::Vec2f Entity::GetDirection() const
    {
        return { std::cosf(mRotation), std::sinf(mRotation) };
    }

    Vec2f Entity::GetRight() const
    {
        return { std::cosf(mRotation + PI/2.0f), std::sinf(mRotation + PI / 2.0f) };
    }

    Vec2f Entity::GetSize() const
    {
        return mSize;
    }

    Vec2f Entity::GetVelocity() const
    {
        return mVelocity;
    }

    bool Entity::IsBlocking() const
    {
        return mBlocking;
    }

    bool Entity::IsMarkedForDestruction() const
    {
        return mMarkedForDestruction;
    }

    void Entity::OnWallCollision()
    {
    }

    void Entity::SetOccupiedTiles()
    {
        const Vec2i minBounds
        {
            std::max(0, static_cast<int32>(mPosition.x) - SPATIAL_PARTITIONING_SIZE),
            std::max(0, static_cast<int32>(mPosition.y) - SPATIAL_PARTITIONING_SIZE),
        };
        const Vec2i maxBounds
        {
            std::min(mLevel.Width - 1, static_cast<int32>(mPosition.x) + SPATIAL_PARTITIONING_SIZE),
            std::min(mLevel.Height - 1, static_cast<int32>(mPosition.y) + SPATIAL_PARTITIONING_SIZE),
        };

        for (int32 y = minBounds.y; y <= maxBounds.y; ++y)
        {
            for (int32 x = minBounds.x; x <= maxBounds.x; ++x)
            {
                Tile& tile = mLevel.GetTile({ x, y });
                mOccupiedTiles.push_back(&tile);
                tile.Entities.insert(this);
            }
        }
    }

    void Entity::ResetOccupiedTiles()
    {
        for(Tile* tile : mOccupiedTiles)
        {
            tile->Entities.erase(this);
        }
        mOccupiedTiles.clear();
    }
}
