//
// Created by danie on 3/13/2024.
//

#include <fstream>
#include "Level1.h"
#include "../HUD.h"

Level1::Level1(Game *game)
        :Scene(game)
        ,mPlayer(nullptr)
{

}

Level1::~Level1()
{
    delete mHUD;
}

void Level1::Load()
{
    // Init HUD
    mHUD = new HUD(this);

    //Load map
    LoadData("../Assets/Levels/level1.txt");
}

void Level1::LoadData(const std::string &filename)
{
    float overlay = 640 - 111.f;

    float floorHeight  = (float)(mGame->GetWindowHeight())*4.5/10;
    SetFloorHeight(floorHeight);

    std::fstream level;
    level.open(filename);
    std::string row;

    std::string texPath = "../Assets/Sprites/Bg/";

    //Tamanho do mapa
    std::getline(level, row);
    int nBackgrounds = std::stoi(row);
    mLevelSize = 640 + ( overlay * (nBackgrounds-1) ) - 660;
    int nFloors = mLevelSize/300;

    for (int n=0;n<nBackgrounds;n++) {
        new Background(this, "../Assets/Sprites/Bg/floor-wall.png", n, mGame->GetWindowHeight(), mGame->GetWindowWidth(), overlay);
    }
}

const Vector2 &Level1::GetCameraPos() {
    return Scene::GetCameraPos();
}
