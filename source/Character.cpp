#include "Character.h"

#include <cmath>
#include <iostream>

Character::Character(b2World &world,
                    float positionX,
                    float positionY,
                    std::vector<std::unique_ptr<Updatable>>& updatables,
                    std::vector<const Renderable*>& renderables,
                    std::vector<Physical*>& physicalUpdatables) 
                    : Physical(physicalUpdatables)
{
    m_rigidBodyDef.type = b2_dynamicBody;
    m_rigidBodyDef.position.Set(positionX, positionY);
    m_rigidBodyDef.linearDamping = 2.f;
    m_rigidBodyDef.angularDamping = 2.f;
    m_rigidBody = world.CreateBody(&m_rigidBodyDef);

    m_dynamicBox.SetAsBox(m_shoulderWidth / 2.f, m_chestSize / 2.f);
    m_fixtureDef.shape = &m_dynamicBox;
    m_fixtureDef.density = m_densityMultiplier;
    m_fixtureDef.friction = 0.4f;
    m_rigidBody->CreateFixture(&m_fixtureDef);
    
    m_characterRectangleShape.setFillColor(sf::Color::White);
    m_characterRectangleShape.setSize({ m_shoulderWidth, m_chestSize });
    m_characterRectangleShape.setOrigin(m_shoulderWidth / 2.f, m_chestSize / 2.f);
    m_characterRectangleShape.setPosition(positionX, positionY);
    m_characterRectangleShape.setRotation(m_rigidBody->GetAngle() * (180.f / b2_pi));

    m_renderZLevel = m_initialRenderZLevel;
    
    m_rigidBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(static_cast<Physical*>(this));
    updatables.emplace_back(this);
    renderables.push_back(this);
}

const sf::Drawable* Character::getDrawable() const
{
    return &m_characterRectangleShape;
}

void Character::update(const float deltaTime, UpdateParameters& updateParameters)
{
    (void)deltaTime;
    (void)updateParameters;
    m_characterRectangleShape.setPosition(m_rigidBody->GetPosition().x, m_rigidBody->GetPosition().y);
    m_characterRectangleShape.setRotation(m_rigidBody->GetAngle() * (180.f / b2_pi));

    if (m_dead == true && m_deadTimerSet == false) {
        m_characterRectangleShape.setFillColor(sf::Color::Green);
        m_deadTimer = std::make_unique<sf::Clock>();
        m_deadTimerSet = true;
        m_deadTimer->restart();
        b2Filter noContact;
        noContact.maskBits = 0;
        releaseRightHandJoin();
        m_rigidBody->GetFixtureList()->SetFilterData(noContact);
    }
    if (m_deadTimer != nullptr && m_removalFlag == false) {
        if (m_deadTimer->getElapsedTime().asSeconds() > 10.f) {
            m_removalFlag = true;
            std::cout << "removing" << std::endl;
            m_deadTimer = nullptr;
        }
    }
}

b2Body* Character::getB2Body() const {
    return m_rigidBody;
}

void Character::joinRightHand(const Grabable* joiningBody) 
{
    if (m_rightHandJoint == nullptr) {
        m_rightHandJointDef.bodyA = m_rigidBody;
        m_rightHandJointDef.bodyB = joiningBody->getB2Body();
        m_rightHandIsGrabbing = joiningBody;
        m_rightHandJointDef.collideConnected = false;
        m_rightHandJoint = m_rigidBody->GetWorld()->CreateJoint(&m_rightHandJointDef);
        m_rightHandIsGrabbing->objectGrabbed();
    }
}

void Character::releaseRightHandJoin()
{
    if (m_rightHandJoint != nullptr) {
        m_rightHandIsGrabbing->objectReleased();
        m_rightHandIsGrabbing = nullptr;
        m_rigidBody->GetWorld()->DestroyJoint(m_rightHandJoint);
        m_rightHandJoint = nullptr;
    }
}

void Character::render(sf::RenderWindow& drawingWindow) const
{
    drawingWindow.draw(m_characterRectangleShape);
}

void Character::physicsUpdate(const float physicsTimeStep, UpdateParameters& updateParameters)
{
    (void)physicsTimeStep;
    (void)updateParameters;
}

void Character::damage(const float valueToDamageBy) {
    m_hp -= valueToDamageBy;

    if (m_hp < 0.f) {
        m_dead = true;
        std::cout << "BLAARGHHDED" << std::endl;
    }
}

void Character::onCollision(const float physicsTimeStep)
{
    //this needs reworking
    const float preMagnitudeThisObject = std::sqrt((std::pow(m_collisionData.m_preSolveLinearVelocityThis.x, 2.f)) + (std::pow(m_collisionData.m_preSolveLinearVelocityThis.y, 2.f)));
    const float preMagnitudeOtherObject = std::sqrt((std::pow(m_collisionData.m_preSolveLinearVelocityOther.x, 2.f)) + (std::pow(m_collisionData.m_preSolveLinearVelocityOther.y, 2.f)));
    const float postMagnitudeThisObject = std::sqrt((std::pow(m_collisionData.m_postSolveLinearVelocityThis.x, 2.f)) + (std::pow(m_collisionData.m_postSolveLinearVelocityThis.y, 2.f)));
    const float postMagnitudeOtherObject = std::sqrt((std::pow(m_collisionData.m_postSolveLinearVelocityOther.x, 2.f)) + (std::pow(m_collisionData.m_postSolveLinearVelocityOther.y, 2.f)));
    const float changeInMagnitudeThisObject = std::abs(preMagnitudeThisObject - postMagnitudeThisObject) /** physicsTimeStep * m_rigidBody->GetMass()*/;
    const float changeInMagnitudeOtherObject = std::abs(preMagnitudeOtherObject - postMagnitudeOtherObject) /** physicsTimeStep * m_collisionData.m_bodyMassOther*/;
    const float changeInAngularVelocityThisObject = std::abs(m_collisionData.m_preSolveAngularVelocityThis - m_collisionData.m_postSolveAngularVelocityThis) /** physicsTimeStep * m_rigidBody->GetMass()*/;
    const float changeInAngularVelocityOtherObject = std::abs(m_collisionData.m_preSolveAngularVelocityOther - m_collisionData.m_postSolveAngularVelocityOther) /** physicsTimeStep * m_collisionData.m_bodyMassOther*/;
    const float damageCalculation = (changeInMagnitudeThisObject + changeInMagnitudeOtherObject + changeInAngularVelocityThisObject + changeInAngularVelocityOtherObject);
     
    if (damageCalculation > 0.5f) {
        std::cout << "damage: " << damageCalculation << std::endl;
        this->damage(damageCalculation);
    }
    clearCollisionData();
    (void)physicsTimeStep;
}