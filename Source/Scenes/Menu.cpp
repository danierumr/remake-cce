//
// Created by danie on 3/13/2024.
//

#include "Menu.h"
#include "../Game.h"
#include "../Font.h"
#include "../Actors/Actor.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"
#include "../Components/DrawComponents/DrawTextComponent.h"

Menu::Menu(Game *game)
        : Scene(game)
        ,mMenuFont(nullptr)
{
    mMenuFont = new Font();
    mMenuFont->Load("../Assets/Fonts/Carlito-Regular.ttf");
}

void Menu::Load()
{
    //Background and Title
    auto* background = new Actor(this);
    new DrawSpriteComponent(background, "../Assets/Sprites/Bg/menu-cce-bg.png", mGame->GetWindowWidth(), mGame->GetWindowHeight(), 0);

    //Press Space label
    auto* pressSpace = new Actor(this);
    pressSpace->SetPosition(Vector2(mGame->GetWindowWidth()/2.0f,mGame->GetWindowHeight() - 42.0f));
    new DrawTextComponent(pressSpace, "Press Space", mMenuFont, 120, 28, 64);
}

void Menu::ProcessInput(const Uint8 *keyState)
{
    if(keyState[SDL_SCANCODE_SPACE])
    {
        mGame->SetScene(Game::GameScene::TestArea);
    }
    else if(keyState[SDL_SCANCODE_ESCAPE])
    {
        mGame->Quit();
    }
}