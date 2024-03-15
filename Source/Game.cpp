// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Random.h"
#include "Game.h"
#include "Actors/Actor.h"
#include "Components/DrawComponents/DrawComponent.h"
#include "Components/DrawComponents/DrawSpriteComponent.h"
#include "Scenes/Menu.h"
#include "Scenes/Level1.h"
#include "Scenes/TestArea.h"

Game::Game(int windowWidth, int windowHeight)
            :mWindow(nullptr)
            ,mRenderer(nullptr)
            ,mAudio(nullptr)
            ,mTicksCount(0)
            ,mIsRunning(true)
            ,mUpdatingActors(false)
            ,mFadeState(FadeState::None)
            ,mSceneTransitionTime(0.0f)
            ,mWindowWidth(windowWidth)
            ,mWindowHeight(windowHeight)
            ,mGameState(GameScene::Menu)
{

}

bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("RE:CCE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWindowWidth, mWindowHeight, 0);
    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }

    // Initialize SDL_ttf
    if (TTF_Init() != 0)
    {
        SDL_Log("Failed to initialize SDL_ttf");
        return false;
    }

    mAudio = new AudioSystem();

    Random::Init();

    mTicksCount = SDL_GetTicks();

    // Init all game actors
    InitializeActors();

    return true;
}

void Game::InitializeActors()
{
    switch (mGameState)
    {
        case GameScene::Menu:
            mScene = new Menu(this);
            mScene->Load();
            break;

        case GameScene::TestArea:
            mScene = new TestArea(this);
            mScene->Load();
            break;

        case GameScene::Level1:
            mScene = new Level1(this);
            mScene->Load();
            break;
        default:
            break;
    }
}

void Game::SetScene(GameScene gameState)
{
    // Stop all sounds
    mAudio->StopAllSounds();
    mFadeState = FadeState::FadeOut;

    // Handle scene transition
    mGameState = gameState;
//    UnloadActors();
//    InitializeActors();
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                Quit();
                break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(nullptr);

    for (auto actor : mActors)
    {
        actor->ProcessInput(state);
    }

    mAudio->ProcessInput(state);
    mScene->ProcessInput(state);
}

void Game::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    mTicksCount = SDL_GetTicks();

    mAudio->Update(deltaTime);

    // Update all actors and pending actors
    UpdateActors(deltaTime);

    // Update camera position
    UpdateCamera();

    if (mFadeState == FadeState::FadeOut)
    {
        mSceneTransitionTime += deltaTime;
        if (mSceneTransitionTime >= SCENE_TRANSITION_TIME)
        {
            mSceneTransitionTime = 0.0f;
            mFadeState = FadeState::FadeIn;

            UnloadActors();
            InitializeActors();
        }
    }
    else if (mFadeState == FadeState::FadeIn)
    {
        mSceneTransitionTime += deltaTime;
        if (mSceneTransitionTime >= SCENE_TRANSITION_TIME)
        {
            mFadeState = FadeState::None;
            mSceneTransitionTime = 0.0f;
        }
    }

}

void Game::UpdateCamera()
{
    mCameraPos = mScene->GetCameraPos() - Vector2(mWindowWidth/2.0f, mWindowHeight/2.0f);
}

void Game::UpdateActors(float deltaTime)
{
    mUpdatingActors = true;
    for (auto actor : mActors)
    {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;

    for (auto pending : mPendingActors)
    {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    std::vector<Actor*> deadActors;
    for (auto actor : mActors)
    {
        if (actor->GetState() == ActorState::Destroy)
        {
            deadActors.emplace_back(actor);
        }
    }

    for (auto actor : deadActors)
    {
        delete actor;
    }
}

void Game::AddActor(Actor* actor)
{
    if (mUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor)
{
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }

    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Game::AddDrawable(class DrawComponent *drawable)
{
    mDrawables.emplace_back(drawable);

    std::sort(mDrawables.begin(), mDrawables.end(),[](DrawComponent* a, DrawComponent* b) {
        return a->GetDrawOrder() < b->GetDrawOrder();
    });
}

void Game::RemoveDrawable(class DrawComponent *drawable)
{
    auto iter = std::find(mDrawables.begin(), mDrawables.end(), drawable);
    mDrawables.erase(iter);
}

void Game::AddCollider(class ColliderComponent *collider)
{
    mColliders[collider->GetLayer()].emplace_back(collider);
}

void Game::RemoveCollider(class ColliderComponent *collider)
{
    auto iter = std::find(mColliders[collider->GetLayer()].begin(), mColliders[collider->GetLayer()].end(), collider);
    mColliders[collider->GetLayer()].erase(iter);
}

void Game::GenerateOutput()
{
    // Set draw color to black
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

    // Clear back buffer
    SDL_RenderClear(mRenderer);

    for (auto drawable : mDrawables)
    {
        if (drawable->IsVisible())
        {
            drawable->Draw(mRenderer);
        }
    }

    // Apply fade effect if changing scene
    if (mFadeState == FadeState::FadeOut)
    {
        SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, static_cast<Uint8>(255 * mSceneTransitionTime/SCENE_TRANSITION_TIME));
        SDL_RenderFillRect(mRenderer, nullptr);
    }
    else if (mFadeState == FadeState::FadeIn)
    {
        SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, static_cast<Uint8>(255 * (1.0f - mSceneTransitionTime/SCENE_TRANSITION_TIME)));
        SDL_RenderFillRect(mRenderer, nullptr);
    }

    // Swap front buffer and back buffer
    SDL_RenderPresent(mRenderer);
}

SDL_Texture* Game::LoadTexture(const std::string& texturePath)
{
    // Load from file
    SDL_Surface* surf = IMG_Load(texturePath.c_str());
    if (!surf)
    {
        SDL_Log("Failed to load texture file %s", texturePath.c_str());
        return nullptr;
    }

    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surf);
    SDL_FreeSurface(surf);
    if (!texture)
    {
        SDL_Log("Failed to convert surface to texture for %s", texturePath.c_str());
        return nullptr;
    }

    return texture;
}

void Game::UnloadActors()
{
    while (!mActors.empty())
    {
        delete mActors.back();
    }

    delete mScene;
}

void Game::Shutdown()
{
    UnloadActors();

    delete mAudio;
    IMG_Quit();

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}