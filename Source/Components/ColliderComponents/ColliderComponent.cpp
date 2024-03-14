//
// Created by Lucas N. Ferreira on 07/12/23.
//

#include "ColliderComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game.h"

ColliderComponent::ColliderComponent(class Actor* owner, ColliderLayer layer, int updateOrder)
        :Component(owner, updateOrder)
        ,mLayer(layer)
{
    mOwner->GetGame()->AddCollider(this);
}

ColliderComponent::~ColliderComponent()
{
    mOwner->GetGame()->RemoveCollider(this);
}