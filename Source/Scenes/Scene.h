//
// Created by Lucas N. Ferreira on 07/12/23.
//

#pragma once

#include <SDL_stdinc.h>
#include "../Math.h"
#include "../Game.h"

class Scene
{
public:
    Scene(class Game* game);

    virtual void Load();
    virtual void ProcessInput(const Uint8* keyState);

    class Game* GetGame() { return mGame; }

    virtual const Vector2& GetCameraPos();

protected:
    class Game* mGame;
};
