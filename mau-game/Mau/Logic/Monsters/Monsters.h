#ifndef MAU_MONSTERS_H
#define MAU_MONSTERS_H

#ifdef _PRAGMA_ONCE_SUPPORT
#pragma once
#endif

#include "Mau/Logic/Monster.h"

namespace Mau
{
    class MonsterLaserPussy : public Monster
    {
    public:
        MonsterLaserPussy(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition);
        void OnFire(const Vec2f& pDirection) override;
    };

    class MonsterBall : public Monster
    {
    public:
        MonsterBall(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition);
        void OnFire(const Vec2f& pDirection) override;
    };

    class MonsterShotgunPussy : public Monster
    {
    public:
        MonsterShotgunPussy(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition);
        void OnFire(const Vec2f& pDirection) override;
    };
}

#endif
