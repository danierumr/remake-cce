// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <SDL.h>
#include <map>
#include <vector>
#include "Math.h"
#include "AudioSystem.h"
#include "Components/ColliderComponents/ColliderComponent.h"


class Game {
public:
    const float SCENE_TRANSITION_TIME = 0.25f;

    enum class GameScene
    {
        Menu,
        Level1
    };

    enum class FadeState
    {
        FadeIn,
        FadeOut,
        None
    };

    Game(int windowWidth, int windowHeight);

    bool Initialize();
    void RunLoop();
    void Shutdown();
    void Quit() { mIsRunning = false; }

    // Actors functions
    void InitializeActors();
    void UpdateActors(float deltaTime);
    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    // Draw functions
    void AddDrawable(class DrawComponent* drawable);
    void RemoveDrawable(class DrawComponent* drawable);

    // Collision functions
    void AddCollider(class ColliderComponent* collider);
    void RemoveCollider(class ColliderComponent* collider);
    std::vector<ColliderComponent*>& GetColliders(ColliderLayer layer) { return mColliders[layer]; }

    // Camera functions
    Vector2& GetCameraPos() { return mCameraPos; };
    void SetCameraPos(const Vector2& position) { mCameraPos = position; };

    void SetScene(GameScene gameState);

    SDL_Renderer* GetRenderer() { return mRenderer; }

    // Window functions
    int GetWindowWidth() const { return mWindowWidth; }
    int GetWindowHeight() const { return mWindowHeight; }

    AudioSystem* GetAudio() { return mAudio; }

    SDL_Texture* LoadTexture(const std::string& texturePath);

private:
    // Core game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    // Auxiliary updates
    void UpdateCamera();

    // Unload actors for scene transition
    void UnloadActors();

    // All the actors in the game
    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;

    // All the draw components
    std::vector<class DrawComponent*> mDrawables;

    // All the collider components
    std::map<ColliderLayer, std::vector<class ColliderComponent*>> mColliders;

    // SDL stuff
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    AudioSystem* mAudio;

    // Window properties
    int mWindowWidth;
    int mWindowHeight;

    // Track elapsed time since game start
    Uint32 mTicksCount;

    // Track if we're updating actors right now
    bool mIsRunning;
    bool mUpdatingActors;

    // Scene transition effect
    FadeState mFadeState;
    float mSceneTransitionTime;

    Vector2 mCameraPos;

    GameScene mGameState;
    class Scene *mScene;

};
