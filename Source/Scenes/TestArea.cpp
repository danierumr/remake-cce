//
// Created by Daniel on 3/14/2024.
//

#include "TestArea.h"
#include "../Actors/Player.h"
#include "../Actors/Wall.h"

TestArea::TestArea(struct Game *game)
        :Scene(game)
        ,mPlayer(nullptr)
{

}

TestArea::~TestArea()
{

}

void TestArea::Load()
{
    // Player
    mPlayer = new Player(this);
    mPlayer->SetPosition(Vector2(mGame->GetWindowWidth()/1.5, mGame->GetWindowHeight()/1.5));

    mCamPos = mPlayer->GetPosition();

    mWall = new Wall(this, 50, 50);
    mWall->SetPosition(Vector2(500, 400));

}

const Vector2 &TestArea::GetCameraPos()
{
    return mCamPos;
}

void TestArea::ProcessInput(const Uint8 *keyState) {
    if(keyState[SDL_SCANCODE_ESCAPE]) {
        mGame->Quit();
    }
}
