#pragma once
#include <box2d/box2d.h>

#include "Updatable.h"

class Physical
{
public:
    Physical::Physical(std::vector<Physical*>& physicalUpdatables){
        physicalUpdatables.push_back(this);
    }
    virtual void physicsUpdate(const float physicsTimeStep, UpdateParameters& updateParameters) = 0;
    struct CollisionData {
        float m_bodyMass = 0.f;
        float m_preSolveAngularVelocity = 0.f;
        b2Vec2 m_preSolveLinearVelocity = { 0.f, 0.f };
        float  m_postSolveAngularVelocity = 0.f;
        b2Vec2 m_postSolveLinearVelocity = { 0.f, 0.f };
    };
    virtual void onCollision(const CollisionData thisObject, const CollisionData otherObject, const float physicsTimeStep) = 0;
    virtual ~Physical() = default;
};

