//
// Created by danie on 3/13/2024.
//

#include "HUD.h"
#include "Font.h"
#include "Actors/Actor.h"
#include "Components/DrawComponents/DrawSpriteComponent.h"
#include "Components/DrawComponents/DrawTextComponent.h"

HUD::HUD(class Scene* scene)
        :mIcon(nullptr)
{
    // Load font
    mMenuFont = new Font();
    mMenuFont->Load("../Assets/Fonts/Carlito-Regular.ttf");


    mIcon = new Actor(scene);
    mIcon->SetPosition( Vector2(200.f, 200.f) );
    new DrawSpriteComponent(mIcon, "../Assets/Sprites/Capivaristo/Capivaristo-Icon.png", 32, 32, 110);

    auto lives = new Actor(scene);
    lives->SetPosition( Vector2(250.f, 250.f) );
    mLives = new DrawTextComponent(lives, "x3", mMenuFont, 32, 16);
}

HUD::~HUD()
{
    delete mMenuFont;
}

void HUD::SetLives(int lives)
{
    std::string livesStr = std::to_string(lives);
    if(livesStr.size() == 1)
        livesStr = "x" + livesStr;

    mLives->SetText(livesStr);
}