#pragma once
#include <box2d/box2d.h>

#include "Updatable.h"



class Physical
{
public:
    Physical::Physical(std::vector<Physical*>& physicalUpdatables);
    virtual void physicsUpdate(const float physicsTimeStep, UpdateParameters& updateParameters) = 0;
    struct CollisionData {
        float m_bodyMassOther = 0.f;

        float m_preSolveAngularVelocityThis = 0.f;
        b2Vec2 m_preSolveLinearVelocityThis = { 0.f, 0.f };
        float  m_postSolveAngularVelocityThis = 0.f;
        b2Vec2 m_postSolveLinearVelocityThis = { 0.f, 0.f };

        float m_preSolveAngularVelocityOther = 0.f;
        b2Vec2 m_preSolveLinearVelocityOther = { 0.f, 0.f };
        float  m_postSolveAngularVelocityOther = 0.f;
        b2Vec2 m_postSolveLinearVelocityOther = { 0.f, 0.f };
    };
    virtual void onCollision(const float physicsTimeStep) = 0;
    virtual ~Physical() = default;

    void setCollisionData(CollisionData collisionDataToSet);
    CollisionData getCollisionData();
    void clearCollisionData();

protected:
    CollisionData m_collisionData;
};

