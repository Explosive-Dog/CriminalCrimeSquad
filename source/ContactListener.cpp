#include "ContactListener.h"

ContactListener::ContactListener(const float physicsTimeStep) : m_physicsTimeStep(physicsTimeStep)
{
}

void ContactListener::BeginContact(b2Contact* contact) {
        std::cout << "Begin Contact" << std::endl;
        (void)contact;
    }

    void ContactListener::EndContact(b2Contact* contact) {
        std::cout << "End Contact" << std::endl;
        (void)contact;
    }

    void ContactListener::PreSolve(b2Contact* contact, const b2Manifold *oldManifold) {

        //std::cout << "Pre Solve" << std::endl;

        collisionDataObjectA.m_preSolveAngularVelocity = contact->GetFixtureA()->GetBody()->GetAngularVelocity();
        collisionDataObjectA.m_preSolveLinearVelocity = contact->GetFixtureA()->GetBody()->GetLinearVelocity();
        collisionDataObjectA.m_bodyMass = contact->GetFixtureA()->GetBody()->GetMass();
        collisionDataObjectB.m_preSolveAngularVelocity = contact->GetFixtureB()->GetBody()->GetAngularVelocity();
        collisionDataObjectB.m_preSolveLinearVelocity = contact->GetFixtureB()->GetBody()->GetLinearVelocity();
        collisionDataObjectB.m_bodyMass = contact->GetFixtureA()->GetBody()->GetMass();

        (void)oldManifold;
    }

    void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {

        //std::cout << "Post Solve" << std::endl;

        collisionDataObjectA.m_postSolveAngularVelocity = contact->GetFixtureA()->GetBody()->GetAngularVelocity();
        collisionDataObjectA.m_postSolveLinearVelocity = contact->GetFixtureA()->GetBody()->GetLinearVelocity();
        collisionDataObjectB.m_postSolveAngularVelocity = contact->GetFixtureB()->GetBody()->GetAngularVelocity();
        collisionDataObjectB.m_postSolveLinearVelocity = contact->GetFixtureB()->GetBody()->GetLinearVelocity();

        auto* const physicalA = reinterpret_cast<Physical*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        //Any b2Body that does not have a nullptr stored in its GetUserData.pointer must be a Physical class.
        if (physicalA != nullptr) {
            physicalA->onCollision(collisionDataObjectA, collisionDataObjectB, m_physicsTimeStep);
            //std::cout << "Here at A." << std::endl;
        }
        auto* const physicalB = reinterpret_cast<Physical*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
        if (physicalB != nullptr) {
            physicalB->onCollision(collisionDataObjectB, collisionDataObjectA, m_physicsTimeStep);
            //std::cout << "Here at B." << std::endl;
        }
        (void)impulse;
    }