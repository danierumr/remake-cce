//
// Created by danie on 3/14/2024.
//

#include "Player.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"

Player::Player(Scene *scene, const float forwardSpeed, int lives)
        : Actor(scene)
        ,mIsDead(false)
        ,mIsAttacking(false)
        ,mAttackTimer(0.0f)
        ,mLives(lives)
{
    mForwardSpeed = forwardSpeed;

    // Draw Component
    mDrawComponent = new DrawAnimatedComponent(this, "../Assets/Sprites/Capivaristo/Capivaristo.png", "../Assets/Sprites/Capivaristo/Capivaristo.json");
    mDrawComponent = new DrawAnimatedComponent(this, "../Assets/Sprites/Capivaristo/Capivaristo.png", "../Assets/Sprites/Capivaristo/Capivaristo.json");
    mDrawComponent->AddAnimation("idle", {1,0});
    mDrawComponent->AddAnimation("run", {4,5,6,5});
    mDrawComponent->AddAnimation("jump", {4});
    mDrawComponent->AddAnimation("punch", {2,3});
    mDrawComponent->AddAnimation("hit", {7,8});
    // Start animation
    mDrawComponent->SetAnimation("idle");
    mDrawComponent->SetAnimFPS(4.0f);


    // Physics related
    mRigidBodyComponent = new RigidBodyComponent(this);
    mBody = new AABBColliderComponent(this, 0, 0, 32, 32, ColliderLayer::Player);

    mShoe = new AABBColliderComponent(this, 0, 0, 32, 32, ColliderLayer::Shoe);
}

void Player::OnProcessInput(const Uint8 *keyState)
{

}