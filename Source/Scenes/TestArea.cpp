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
    mPlayer->SetPosition(Vector2(mGame->GetWindowWidth()/2.f, mGame->GetWindowHeight()/2.f));

    //mCamPos = mPlayer->GetPosition();
    mCamPos = Vector2(mGame->GetWindowWidth()/2.f, mGame->GetWindowHeight()/2.f);



    // Barriers
    float middleHeight = mGame->GetWindowHeight()/2.f;
    Vector2 posAux = mCamPos + (Vector2(0,-middleHeight/2.f));
    mWallMiddle = new Wall(this, 1000, middleHeight);
    mWallMiddle->SetPosition(posAux);

    float sideWidth = 200;
    posAux = mCamPos + (Vector2(mGame->GetWindowWidth()/2.f+sideWidth/2.f,0));
    mWallRight = new Wall(this, sideWidth, 1000);
    mWallRight->SetPosition(posAux);

    posAux = mCamPos - (Vector2(mGame->GetWindowWidth()/2.f+sideWidth/2.f,0));
    mWallLeft = new Wall(this, sideWidth, 1000);
    mWallLeft->SetPosition(posAux);


}

const Vector2 &TestArea::GetCameraPos()
{

    // TODO Follow character and change walls position
    return mCamPos;
}

void TestArea::ProcessInput(const Uint8 *keyState) {
    if(keyState[SDL_SCANCODE_ESCAPE]) {
        mGame->Quit();
    }
}
