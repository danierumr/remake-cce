//
// Created by danie on 3/13/2024.
//

#pragma once

#include <string>
#include "Scene.h"
#include <vector>
#include "../Actors/Background.h"

class Level1 : public Scene
{
public:
    Level1(class Game* game);
    ~Level1();

    void Load() override;
    const Vector2& GetCameraPos() override;

    class HUD* GetHUD() { return mHUD; }


    // Game Specifics
    void SetFloorHeight(float floorHeight) {mFloorHeight = floorHeight; }

private:
    void LoadData(const std::string& filename);

    class Player* mPlayer;
    class HUD* mHUD;


    // Game Specifics
    float mFloorHeight;
    float mLevelSize;
};