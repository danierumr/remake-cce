//
// Created by danie on 3/13/2024.
//

#pragma once

class HUD
{
public:
    HUD(class Scene* scene);
    ~HUD();

    void SetLives(int lives);
    void SetHealth(int health);

private:
    class Actor* mIcon;

    // HUD elements
    class DrawTextComponent* mLives;
    class DrawTextComponent* mHealthBar;

    class Font *mMenuFont;
};
