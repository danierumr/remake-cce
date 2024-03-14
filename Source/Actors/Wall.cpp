//
// Created by Lucas N. Ferreira on 16/11/23.
//

#include "Wall.h"
#include "../Game.h"
#include "../Components/ColliderComponents/AABBColliderComponent.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"

Wall::Wall(Scene* scene, int width, int height)
        :Actor(scene)
{
    mAA = new AABBColliderComponent(this, 0, 0, width, height, ColliderLayer::Wall);


    //Debug
    auto v1 = mAA->GetMin();
    auto v4 = mAA->GetMax();
    Vector2 v2 = Vector2(v4.x, v1.y);
    Vector2 v3 = Vector2(v1.x, v4.y);
    // Put them into array
    mDrawDebug = new DrawPolygonComponent(this, { v1,v2, v4, v3 });
}

void Wall::OnUpdate(float deltaTime)
{
    //Debug
    auto v1 = mAA->GetMin();
    auto v4 = mAA->GetMax();
    Vector2 v2 = Vector2(v4.x, v1.y);
    Vector2 v3 = Vector2(v1.x, v4.y);
    // Put them into array
    mDrawDebug->SetVertices({ v1,v2, v4, v3 });
}
