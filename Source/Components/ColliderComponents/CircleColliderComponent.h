//
// Created by Lucas N. Ferreira on 10/09/23.
//

#pragma once
#include "../ColliderComponents/ColliderComponent.h"
#include "../../Math.h"
#include <vector>

class CircleColliderComponent : public ColliderComponent
{
public:
    CircleColliderComponent(class Actor* owner, float radius, ColliderLayer layer, int updateOrder);

    void SetRadius(float radius) { mRadius = radius; }
    float GetRadius() const;

    const Vector2 GetCenter() const override;

    bool Intersect(const CircleColliderComponent& b) const;

private:
    float mRadius;
};

