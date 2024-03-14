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

    // Movement
    Vector2 velocity = mRigidBodyComponent->GetVelocity();
    bool pressedMovementKey = false;
    velocity.x = 0.0f;
    // Move right
    if(keyState[SDL_SCANCODE_D])
    {
        mRigidBodyComponent->ApplyForce(Vector2(mForwardSpeed,0));
        mRotation = 0.0f;

        pressedMovementKey = true;
        velocity.x = 1.0f;
    }
    // Move left
    if(keyState[SDL_SCANCODE_A])
    {
        mRigidBodyComponent->ApplyForce(Vector2(-1 * mForwardSpeed,0));
        mRotation = Math::Pi;

        pressedMovementKey = true;
        velocity.x = -1.0f;
    }
    // Move up
    if(keyState[SDL_SCANCODE_W])
    {
        mRigidBodyComponent->ApplyForce(Vector2(0,-1 * mForwardSpeed));

        pressedMovementKey = true;
        velocity.y = -1.0f;
    }
    // Move down
    if(keyState[SDL_SCANCODE_S])
    {
        mRigidBodyComponent->ApplyForce(Vector2(0,mForwardSpeed));

        pressedMovementKey = true;
        velocity.y = 1.0f;
    }
    if(pressedMovementKey) {
        velocity.Normalize();
        mRigidBodyComponent->SetVelocity(velocity * mForwardSpeed);
    }





    // Punch
    if(!mIsAttacking && keyState[SDL_SCANCODE_P])
    {
        // TODO Play sound
        mIsAttacking = true;
    }

    // Jump
    if(keyState[SDL_SCANCODE_SPACE])
    {
        // TODO Jump
    }
}

void Player::OnUpdate(float deltaTime)
{

    // Attack
    if(mIsAttacking) {
        mAttackTimer += deltaTime;
        if(mAttackTimer >= .5f) {
            mIsAttacking = false;
            mAttackTimer = 0.0f;
        }
    }

    // Animations
    UpdateAnimations();

    mRigidBodyComponent->SetVelocity(Vector2::Zero);
}


void Player::UpdateAnimations()
{
    Vector2 velocity = mRigidBodyComponent->GetVelocity();


    if (mIsAttacking && mAttackTimer <= .25f) {
        mDrawComponent->SetAnimation("punch", false);
        mDrawComponent->SetAnimFPS(8.f);
    }
    else {
        mDrawComponent->SetAnimFPS(4.f);
        if ( !Math::NearZero(velocity.x, 15) || !Math::NearZero(velocity.y, 15)) {
            mDrawComponent->SetAnimation("run");
        }
        else {
            mDrawComponent->SetAnimation("idle");
        }
    }
}