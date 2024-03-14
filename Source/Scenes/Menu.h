//
// Created by danie on 3/13/2024.
//

#pragma once

#include "Scene.h"

class Menu : public Scene
{
public:
    Menu(class Game* game);

    void Load() override;
    void ProcessInput(const Uint8* keyState) override;

private:
    class Font *mMenuFont;
};
