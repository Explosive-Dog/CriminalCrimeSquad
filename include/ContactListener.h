#pragma once
#include <box2d/box2d.h>

#include "Character.h"
#include "Physical.h"

#include<iostream>
#include<memory>


class ContactListener : public b2ContactListener
{
public:
    ContactListener(const float physicsTimeStep);

    void BeginContact(b2Contact* contact) override;

    void EndContact(b2Contact* contact) override;
	
    void PreSolve(b2Contact* contact, const b2Manifold *oldManifold) override;
	
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

private:
    const float m_physicsTimeStep = 0.f;
    Physical::CollisionData collisionDataObjectA;
    Physical::CollisionData collisionDataObjectB;
};