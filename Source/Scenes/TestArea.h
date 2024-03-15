//
// Created by Daniel on 3/14/2024.
//

#pragma onde
#include "Scene.h"

class TestArea : public Scene
{
public:
    TestArea(class Game* game);
    ~TestArea();

    void Load() override;
    const Vector2& GetCameraPos() override;

    void ProcessInput(const Uint8* keyState) override;

private:

    class Player *mPlayer;

    Vector2 mCamPos;

    // Barriers
    class Wall *mWallMiddle;
    class Wall *mWallLeft;
    class Wall *mWallRight;

};
