//
// Created by Lucas N. Ferreira on 28/09/23.
//

#include "DrawSpriteComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game.h"

DrawSpriteComponent::DrawSpriteComponent(class Actor* owner, const std::string &texturePath, const int width, const int height, const int drawOrder, const bool isHUD)
        :DrawComponent(owner, drawOrder)
        ,mWidth(width)
        ,mHeight(height)
        ,mIsFlippedHorizontally(false)
        ,mIsFlippedVertically(false)
        ,mIsHUD(isHUD)
{
    // Load sprite sheet texture
    mSpriteSheetSurface = mOwner->GetGame()->LoadTexture(texturePath);
}

DrawSpriteComponent::~DrawSpriteComponent()
{
    SDL_DestroyTexture(mSpriteSheetSurface);
}

void DrawSpriteComponent::Draw(SDL_Renderer *renderer)
{
    Vector2 pos = mOwner->GetPosition();
    Vector2 cameraPos = mOwner->GetGame()->GetCameraPos();

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if(mOwner->GetDirectionVector().y < .0f && mIsFlippedVertically) {
        flip = SDL_FLIP_VERTICAL;
    }
    else if (mOwner->GetDirectionVector().x < .0f && mIsFlippedHorizontally) {
        flip = SDL_FLIP_HORIZONTAL;
    }

    Vector2 cameraOffset = mIsHUD ? Vector2::Zero : cameraPos;
    Vector2 sizeOffset = mIsHUD ? Vector2::Zero : Vector2(mWidth, mHeight) * 0.5f;

    SDL_Rect renderQuad = {static_cast<int>(pos.x - sizeOffset.x - cameraOffset.x),
                           static_cast<int>(pos.y - sizeOffset.y - cameraOffset.y),
                           mWidth,
                           mHeight};

    SDL_RenderCopyEx(renderer, mSpriteSheetSurface, nullptr, &renderQuad, .0f, nullptr, flip);
}
