//
// Created by Lucas N. Ferreira on 28/09/23.
//

#pragma once
#include "DrawComponent.h"

class DrawPolygonComponent : public DrawComponent
{
public:
    // (Lower draw order corresponds with further back)
    DrawPolygonComponent(class Actor* owner, const std::vector<Vector2> &vertices, int drawOrder = 100);

    void Draw(SDL_Renderer* renderer) override;

    std::vector<Vector2>& GetVertices() { return mVertices; }
    void SetVertices(const std::vector<Vector2>& vertices) { mVertices = vertices; }

protected:
    int mDrawOrder;
    std::vector<Vector2> mVertices;
};