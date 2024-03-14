// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include <SDL_stdinc.h>
#include "../Math.h"
#include "../Scenes/Scene.h"
#include "../Components/ColliderComponents/AABBColliderComponent.h"
#include <map>

enum class ActorState
{
    Active,
    Paused,
    Destroy
};

enum class Direction
{
    Center,
    Up,
    Right,
    Down,
    Left,
};

class Actor
{
public:
    Actor(class Scene* scene);
    virtual ~Actor();

    // Update function called from Game (not overridable)
    void Update(float deltaTime);
    // ProcessInput function called from Game (not overridable)
    void ProcessInput(const Uint8* keyState);

    // Position getter/setter
    const Vector2& GetPosition() const { return mPosition; }
    void SetPosition(const Vector2& pos) { mPosition = pos; }

    Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

    // Scale getter/setter
    float GetScale() const { return mScale; }
    void SetScale(float scale) { mScale = scale; }

    // Rotation getter/setter
    float GetRotation() const { return mRotation; }
    void SetRotation(float rotation) { mRotation = rotation; }

    // GameScene getter/setter
    ActorState GetState() const { return mState; }
    void SetState(ActorState state) { mState = state; }

    // Game getter
    class Game* GetGame() { return mScene->GetGame(); }

    // Returns component of type T, or null if doesn't exist
    template <typename T>
    T* GetComponent() const
    {
        for (auto c : mComponents)
        {
            T* t = dynamic_cast<T*>(c);
            if (t != nullptr)
            {
                return t;
            }
        }

        return nullptr;
    }

    // Game specific
    Direction& GetDirection() { return mDirection; }
    const Vector2& GetDirectionVector() const { return mDirectionVectors.at(mDirection); }

    // Any actor-specific collision code (overridable)
    virtual void DetectCollision();
    virtual void OnCollision(std::vector<AABBColliderComponent::Overlap>& responses);

    float GetForwardSpeed() const { return mForwardSpeed; }

protected:
    class Scene* mScene;

    // Any actor-specific update code (overridable)
    virtual void OnUpdate(float deltaTime);
    // Any actor-specific update code (overridable)
    virtual void OnProcessInput(const Uint8* keyState);

    // Actor's state
    ActorState mState;

    // Transform
    Vector2 mPosition;
    float mScale;
    float mRotation;

    // Components
    std::vector<class Component*> mComponents;

    // Game specific
    Direction mDirection;
    const std::map<Direction, Vector2> mDirectionVectors = {
            {Direction::Center, Vector2(0, 0)},
            {Direction::Up, Vector2(0, -1)},
            {Direction::Right, Vector2(1, 0)},
            {Direction::Down, Vector2(0, 1)},
            {Direction::Left, Vector2(-1, 0)}
    };

    float mForwardSpeed;

private:
    friend class Component;

    // Adds component to Actor (this is automatically called
    // in the component constructor)
    void AddComponent(class Component* c);
};