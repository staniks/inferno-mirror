#include "Mau/States/Gameplay/GameplayState.h"
#include "Monsters.h"
#include "Mau/Logic/Projectiles/Projectiles.h"
#include "Mau/Math/Math.h"

namespace Mau
{
    MonsterLaserPussy::MonsterLaserPussy(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition)
        :
        Monster(pGameplayState, pLevel, pPosition,
                50,
                3,
                0.0001f,
                std::vector<std::vector<std::string>>
                {
                    std::vector<std::string>
                    {
                        "enemy_01/walk/0000.png",
                        "enemy_01/walk/0001.png",
                        "enemy_01/walk/0002.png",
                        "enemy_01/walk/0003.png",
                        "enemy_01/walk/0004.png",
                        "enemy_01/walk/0005.png",
                        "enemy_01/walk/0006.png",
                        "enemy_01/walk/0007.png",
                        "enemy_01/walk/0008.png",
                        "enemy_01/walk/0009.png",
                        "enemy_01/walk/0010.png"
                    },
                    std::vector<std::string>
                    {
                        "enemy_01/attack/0020.png",
                        "enemy_01/attack/0021.png",
                        "enemy_01/attack/0022.png",
                        "enemy_01/attack/0023.png",
                        "enemy_01/attack/0024.png",
                        "enemy_01/attack/0025.png",
                        "enemy_01/attack/0026.png",
                        "enemy_01/attack/0027.png",
                        "enemy_01/attack/0028.png",
                        "enemy_01/attack/0029.png",
                        "enemy_01/attack/0030.png",
                        "enemy_01/attack/0030.png",
                        "enemy_01/attack/0030.png",
                        "enemy_01/attack/0030.png",
                        "enemy_01/attack/0030.png",
                        "enemy_01/attack/0030.png",
                        "enemy_01/attack/0030.png",
                        "enemy_01/attack/0030.png",
                        "enemy_01/attack/0030.png",
                        "enemy_01/attack/0030.png",
                        "enemy_01/attack/0030.png",
                        "enemy_01/attack/0030.png",
                        "enemy_01/attack/0030.png",
                        "enemy_01/attack/0030.png",
                        "enemy_01/attack/0030.png",
                    },
                    std::vector<std::string>
                    {
                        "enemy_01/death/0050.png",
                        "enemy_01/death/0051.png",
                        "enemy_01/death/0052.png",
                        "enemy_01/death/0053.png",
                        "enemy_01/death/0054.png",
                        "enemy_01/death/0055.png",
                        "enemy_01/death/0056.png",
                        "enemy_01/death/0057.png",
                        "enemy_01/death/0058.png",
                        "enemy_01/death/0059.png",
                        "enemy_01/death/0060.png",
                        "enemy_01/death/0061.png",
                        "enemy_01/death/0062.png",
                        "enemy_01/death/0063.png",
                        "enemy_01/death/0064.png",
                        "enemy_01/death/0065.png",
                    }
                }
        )
    {
    }

    void MonsterLaserPussy::OnFire(const Vec2f& pDirection)
    {
        Vec2f velocity = pDirection * 0.0075f;
        mLevel.Spawn(std::make_unique<ProjectileEnemyPlasma>(mGameplayState, mLevel, mPosition, velocity, this));
    }

    MonsterBall::MonsterBall(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition)
        :
        Monster(pGameplayState, pLevel, pPosition,
                100,
                3,
                0.000045f,
                std::vector<std::vector<std::string>>
                {
                    std::vector<std::string>
                    {
                        "enemy_02/attack/0000.png",
                    },
                    std::vector<std::string>
                    {
                        "enemy_02/attack/0000.png",
                        "enemy_02/attack/0001.png",
                        "enemy_02/attack/0002.png",
                        "enemy_02/attack/0003.png",
                        "enemy_02/attack/0004.png",
                        "enemy_02/attack/0005.png",
                        "enemy_02/attack/0006.png",
                        "enemy_02/attack/0007.png",
                        "enemy_02/attack/0008.png",
                        "enemy_02/attack/0009.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                        "enemy_02/attack/0010.png",
                    },
                    std::vector<std::string>
                    {
                        "enemy_02/death/0030.png",
                        "enemy_02/death/0031.png",
                        "enemy_02/death/0032.png",
                        "enemy_02/death/0033.png",
                        "enemy_02/death/0034.png",
                        "enemy_02/death/0035.png",
                        "enemy_02/death/0036.png",
                        "enemy_02/death/0037.png",
                        "enemy_02/death/0038.png",
                        "enemy_02/death/0039.png",
                        "enemy_02/death/0040.png",
                    }
                }
        )
    {
    }

    void MonsterBall::OnFire(const Vec2f& pDirection)
    {
        Vec2f velocity = pDirection * 0.0025f;
        mLevel.Spawn(std::make_unique<ProjectileEnemyTracking>(mGameplayState, mLevel, mPosition, velocity, this));
    }

    MonsterShotgunPussy::MonsterShotgunPussy(GameplayState& pGameplayState, Level& pLevel, Mau::Vec2f pPosition)
        :
        Monster(pGameplayState, pLevel, pPosition,
                50,
                3,
                0.0001f,
                std::vector<std::vector<std::string>>
                {
                    std::vector<std::string>
                    {
                        "enemy_03/walk/0000.png",
                        "enemy_03/walk/0001.png",
                        "enemy_03/walk/0002.png",
                        "enemy_03/walk/0003.png",
                        "enemy_03/walk/0004.png",
                        "enemy_03/walk/0005.png",
                        "enemy_03/walk/0006.png",
                        "enemy_03/walk/0007.png",
                        "enemy_03/walk/0008.png",
                        "enemy_03/walk/0009.png",
                        "enemy_03/walk/0010.png",
                        "enemy_03/walk/0011.png",
                        "enemy_03/walk/0012.png",
                        "enemy_03/walk/0013.png",
                        "enemy_03/walk/0014.png",
                        "enemy_03/walk/0015.png",
                        "enemy_03/walk/0016.png",
                        "enemy_03/walk/0017.png",
                        "enemy_03/walk/0018.png",
                        "enemy_03/walk/0019.png",
                        "enemy_03/walk/0020.png"
                    },
                    std::vector<std::string>
                    {
                        "enemy_03/attack/0040.png",
                        "enemy_03/attack/0041.png",
                        "enemy_03/attack/0042.png",
                        "enemy_03/attack/0043.png",
                        "enemy_03/attack/0044.png",
                        "enemy_03/attack/0045.png",
                        "enemy_03/attack/0046.png",
                        "enemy_03/attack/0047.png",
                        "enemy_03/attack/0048.png",
                        "enemy_03/attack/0049.png",
                        "enemy_03/attack/0050.png",
                        "enemy_03/attack/0050.png",
                        "enemy_03/attack/0050.png",
                        "enemy_03/attack/0050.png",
                        "enemy_03/attack/0050.png",
                        "enemy_03/attack/0050.png",
                        "enemy_03/attack/0050.png",
                        "enemy_03/attack/0050.png",
                        "enemy_03/attack/0050.png"
                    },
                    std::vector<std::string>
                    {
                        "enemy_03/death/0060.png",
                        "enemy_03/death/0061.png",
                        "enemy_03/death/0062.png",
                        "enemy_03/death/0063.png",
                        "enemy_03/death/0064.png",
                        "enemy_03/death/0065.png",
                        "enemy_03/death/0066.png",
                        "enemy_03/death/0067.png",
                        "enemy_03/death/0068.png",
                        "enemy_03/death/0069.png",
                        "enemy_03/death/0070.png"
                    }
                }
        )
    {
    }

    void MonsterShotgunPussy::OnFire(const Vec2f& pDirection)
    {
        Vec2f velocity = pDirection * 0.005f;
        const float spread = 0.175f;

        const float rotation = std::atan2f(pDirection.y, pDirection.x);

        const Vec2f right{std::cosf(rotation + PI / 2.0f), std::sinf(rotation + PI / 2.0f)};

        mLevel.Spawn(
            std::make_unique<ProjectileEnemyShotgun
            >(mGameplayState, mLevel, mPosition + right * spread, velocity, this));
        mLevel.Spawn(
            std::make_unique<ProjectileEnemyShotgun
            >(mGameplayState, mLevel, mPosition - right * spread, velocity, this));
    }
}
