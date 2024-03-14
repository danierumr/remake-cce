//
// Created by Daniel Monteiro Rosado on 13/12/23.
//
#pragma once

#include "Actor.h"
#include "../Scenes/Scene.h"

class Background : public Actor{
public:
    explicit Background(Scene* scene, const std::string &texturePath, int id, int wHeight, int wWidth, float overlay);
};
