#include "ContactListener.h"

ContactListener::ContactListener(const float physicsTimeStep) : m_physicsTimeStep(physicsTimeStep)
{
}

Physical::CollisionData ContactListener::generateCollisionData(bool aOrB, bool preOrPost, b2Contact* contact)
{
    Physical::CollisionData collisionData;

    switch (aOrB)
    {
    case a:
        switch (preOrPost)
        {
        case pre:
            collisionData.m_preSolveAngularVelocityThis = contact->GetFixtureA()->GetBody()->GetAngularVelocity();
            collisionData.m_preSolveLinearVelocityThis = contact->GetFixtureA()->GetBody()->GetLinearVelocity();
            collisionData.m_preSolveAngularVelocityOther = contact->GetFixtureB()->GetBody()->GetAngularVelocity();
            collisionData.m_preSolveLinearVelocityOther = contact->GetFixtureB()->GetBody()->GetLinearVelocity();
            collisionData.m_bodyMassOther = contact->GetFixtureB()->GetBody()->GetMass();
            break;
        case post:
            auto* const physicalA = reinterpret_cast<Physical*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
            collisionData = physicalA->getCollisionData();
            collisionData.m_postSolveAngularVelocityThis = contact->GetFixtureA()->GetBody()->GetAngularVelocity();
            collisionData.m_postSolveLinearVelocityThis = contact->GetFixtureA()->GetBody()->GetLinearVelocity();
            collisionData.m_postSolveAngularVelocityOther = contact->GetFixtureB()->GetBody()->GetAngularVelocity();
            collisionData.m_postSolveLinearVelocityOther = contact->GetFixtureB()->GetBody()->GetLinearVelocity();
            break;
        }
        break;
    case b:
        switch (preOrPost)
        {
        case pre:
            collisionData.m_preSolveAngularVelocityThis = contact->GetFixtureB()->GetBody()->GetAngularVelocity();
            collisionData.m_preSolveLinearVelocityThis = contact->GetFixtureB()->GetBody()->GetLinearVelocity();
            collisionData.m_preSolveAngularVelocityOther = contact->GetFixtureA()->GetBody()->GetAngularVelocity();
            collisionData.m_preSolveLinearVelocityOther = contact->GetFixtureA()->GetBody()->GetLinearVelocity();
            collisionData.m_bodyMassOther = contact->GetFixtureA()->GetBody()->GetMass();
            break;

        case post:
            auto* const physicalB = reinterpret_cast<Physical*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
            collisionData = physicalB->getCollisionData();
            collisionData.m_postSolveAngularVelocityThis = contact->GetFixtureB()->GetBody()->GetAngularVelocity();
            collisionData.m_postSolveLinearVelocityThis = contact->GetFixtureB()->GetBody()->GetLinearVelocity();
            collisionData.m_postSolveAngularVelocityOther = contact->GetFixtureA()->GetBody()->GetAngularVelocity();
            collisionData.m_postSolveLinearVelocityOther = contact->GetFixtureA()->GetBody()->GetLinearVelocity();
            break;
        }
        break;
    }

    return collisionData;
}

void ContactListener::BeginContact(b2Contact* contact) {
        //std::cout << "Begin Contact" << std::endl;
        (void)contact;
}

void ContactListener::EndContact(b2Contact* contact) {
    //std::cout << "End Contact" << std::endl;
    (void)contact;
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold *oldManifold) {

    //std::cout << "Pre Solve" << std::endl;

    //Any b2Body that does not have a nullptr stored in its GetUserData.pointer must be a Physical class.
    auto* const physicalA = reinterpret_cast<Physical*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    if (physicalA != nullptr) {
        physicalA->setCollisionData(generateCollisionData(a, pre, contact));
    }
    auto* const physicalB = reinterpret_cast<Physical*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
    if (physicalB != nullptr) {
        physicalB->setCollisionData(generateCollisionData(b, pre, contact));
    }
    (void)oldManifold;
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {

    //std::cout << "Post Solve" << std::endl;

    //Any b2Body that does not have a nullptr stored in its GetUserData.pointer must be a Physical class.
    auto* const physicalA = reinterpret_cast<Physical*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    if (physicalA != nullptr) {
        physicalA->setCollisionData(generateCollisionData(a, post, contact));
        physicalA->onCollision(m_physicsTimeStep);
    }
    auto* const physicalB = reinterpret_cast<Physical*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
    if (physicalB != nullptr) {
        physicalB->setCollisionData(generateCollisionData(b, post, contact));
        physicalB->onCollision(m_physicsTimeStep);
    }
    (void)impulse;
}


