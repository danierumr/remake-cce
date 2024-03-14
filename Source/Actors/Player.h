//
// Created by danie on 3/14/2024.
//

#pragma once
#include "Actor.h"
#include "../Scenes/Scene.h"

class Player : public Actor
{
public:
    Player(Scene* scene, float forwardSpeed = 250.0f, int lives = 3);

    void OnProcessInput(const Uint8* keyState) override;
    void OnUpdate(float deltaTime) override;

    void DetectCollision() override;
    void OnCollision(std::vector<AABBColliderComponent::Overlap>& responses) override;


    int GetLives() const { return mLives; }

private:

    bool mIsDead;

    void UpdateAnimations();

    // Colliders
    class RigidBodyComponent* mRigidBodyComponent;
    class DrawAnimatedComponent*  mDrawComponent;
    class AABBColliderComponent* mBody;
    class AABBColliderComponent* mPunch;
    class AABBColliderComponent* mShoe;
    // Debug
    class DrawPolygonComponent* mDrawDebugComponent;

    bool mIsAttacking;
    float mAttackTimer;

    int mLives;
};