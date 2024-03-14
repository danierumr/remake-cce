cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME "remake-cce")
project(${PROJECT_NAME})
add_executable(${PROJECT_NAME}
        Source/Main.cpp
        Source/AudioSystem.cpp
        Source/AudioSystem.h
        Source/CSV.h
        Source/Font.cpp
        Source/Font.h
        Source/Json.h
        Source/Math.cpp
        Source/Math.h
        Source/Random.cpp
        Source/Random.h
        Source/Game.cpp
        Source/Game.h
        Source/Scenes/Menu.cpp
        Source/Scenes/Menu.h
        Source/Scenes/Scene.h
        Source/Components/DrawComponents/DrawAnimatedComponent.h
        Source/Scenes/Level1.cpp
        Source/Scenes/Level1.h
        Source/HUD.cpp
        Source/HUD.h
        Source/Scenes/Scene.cpp
        Source/Actors/Actor.cpp
        Source/Actors/Background.cpp
        Source/Components/RigidBodyComponent.cpp
        Source/Components/Component.cpp
        Source/Components/AIComponents/FSMComponent.cpp
        Source/Components/AIComponents/FSMState.cpp
        Source/Components/ColliderComponents/ColliderComponent.cpp
        Source/Components/ColliderComponents/CircleColliderComponent.cpp
        Source/Components/ColliderComponents/AABBColliderComponent.cpp
        Source/Components/DrawComponents/DrawAnimatedComponent.cpp
        Source/Components/DrawComponents/DrawComponent.cpp
        Source/Components/DrawComponents/DrawPolygonComponent.cpp
        Source/Components/DrawComponents/DrawSpriteComponent.cpp
        Source/Components/DrawComponents/DrawTextComponent.cpp
        Source/Components/DrawComponents/DrawTileComponent.cpp
        Source/Actors/Player.cpp
        Source/Actors/Player.h
)


####### DO NOT EDIT BELLOW
find_package(SDL2 2.28.2 EXACT REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf)