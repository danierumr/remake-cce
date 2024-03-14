//
// Created by Lucas N. Ferreira on 28/09/23.
//

#pragma once
#include "../ColliderComponents/ColliderComponent.h"
#include "../../Math.h"
#include "../RigidBodyComponent.h"
#include <vector>
#include <set>

enum class CollisionSide
{
    Top,
    Down,
    Left,
    Right
};

class AABBColliderComponent : public ColliderComponent
{
public:
    struct Overlap
    {
        Vector2 distance;
        CollisionSide side;
        AABBColliderComponent *source{};
        AABBColliderComponent *target{};
    };

    AABBColliderComponent(class Actor* owner, int dx, int dy, int w, int h,
                                ColliderLayer layer, int updateOrder = 20);

    bool Intersect(const AABBColliderComponent& b) const;
    void DetectCollision(RigidBodyComponent *rigidBody, std::vector<class AABBColliderComponent*>& colliders);
    void ResolveCollisions(RigidBodyComponent *rigidBody, const Overlap& minOverlap);

    const Vector2 GetMin() const;
    const Vector2 GetMax() const;
    const Vector2 GetCenter() const override;

    void SetOffset(const Vector2& offset) { mOffset = offset; }
    void SetWidth(int width) { mWidth = width; }
    void SetHeight(int height) { mHeight = height; }

private:
    Overlap GetMinOverlap(AABBColliderComponent* b) const;

    Vector2 mOffset;
    int mWidth;
    int mHeight;
};