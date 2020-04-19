cmake_minimum_required (VERSION 3.2)
project (Mau-Game)

include(${CMAKE_SOURCE_DIR}/cmake/SDL_Mac.cmake)

set (CMAKE_C_FLAGS_DEBUG "-g")
set (CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

set (CMAKE_CXX_FLAGS_DEBUG "-std=c++17")
set (CMAKE_CXX_FLAGS_RELEASE "-std=c++17")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(Base
  Mau/Base/Engine.cpp
  Mau/Base/RenderDevice.cpp
  Mau/Base/State.cpp)

add_library(IO
  Mau/IO/Log.cpp
  Mau/IO/Resource.cpp
  Mau/IO/Resources/BitmapFont.cpp
  Mau/IO/Resources/LexData.cpp
  Mau/IO/Resources/Sound.cpp
  Mau/IO/Resources/TextData.cpp
  Mau/IO/Resources/Texture.cpp)

add_library(Logic
  Mau/Logic/Entity.cpp
  Mau/Logic/Level.cpp
  Mau/Logic/Monster.cpp
  Mau/Logic/Monsters/Monsters.cpp
  Mau/Logic/Particle.cpp
  Mau/Logic/Pickup.cpp
  Mau/Logic/Pickups/PickupAmmo.cpp
  Mau/Logic/Pickups/PickupExit.cpp
  Mau/Logic/Pickups/PickupHealth.cpp
  Mau/Logic/Pickups/PickupKeycard.cpp
  Mau/Logic/Pickups/PickupRelic.cpp
  Mau/Logic/Pickups/PickupWeapons.cpp
  Mau/Logic/Player.cpp
  Mau/Logic/Projectile.cpp
  Mau/Logic/Projectiles/Projectiles.cpp
  Mau/Logic/Weapon.cpp)

add_library(Math
  Mau/Math/Math.cpp
  Mau/Math/Rect.cpp)

add_library(MauSDL
  Mau/SDL/SDLSystems.cpp)

add_library(States
  Mau/States/Gameplay/GameplayState.cpp
  Mau/States/Gameplay/Resources/DialogueRepository.cpp
  Mau/States/Gameplay/Substates/DialogueState.cpp
  Mau/States/Gameplay/Substates/QuitPromptState.cpp
  Mau/States/MainMenu/MainMenuState.cpp
  Mau/States/Story/StoryState.cpp
  Mau/States/Story/StoryState.cpp)

add_executable(mau mau-game.cpp)

target_link_libraries(mau
  Base
  IO
  Logic
  Math
  States
  MauSDL
  ${SDL2_LINK_LIBRARIES})
