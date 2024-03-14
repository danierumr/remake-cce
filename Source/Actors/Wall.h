//
// Created by Lucas N. Ferreira on 16/11/23.
//

#pragma once

#include "Actor.h"
#include "../Scenes/Scene.h"

class Wall : public Actor
{
public:
    Wall(Scene* game, int width, int height);
//    ~Wall();

    void OnUpdate(float deltaTime) override;

private:
    class DrawPolygonComponent* mDrawDebug;
    class AABBColliderComponent* mAA;
};
