//
// Created by Lucas N. Ferreira on 07/12/23.
//

#pragma once
#include "../Component.h"
#include "../../Math.h"

enum class ColliderLayer
{
    Player,
    Enemy,
    Wall,
    Item,
    Node,
    Bush,
    Sword,
    Shoe,
    Punch
};

class ColliderComponent : public Component
{
public:
    // (Lower draw order corresponds with further back)
    explicit ColliderComponent(class Actor* owner, ColliderLayer layer, int updateOrder);
    ~ColliderComponent() override;

    ColliderLayer GetLayer() const { return mLayer; }

    virtual const Vector2 GetCenter() const { return Vector2::Zero; }

protected:
    ColliderLayer mLayer;
};
