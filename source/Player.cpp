#include "Player.h"
#include <iostream>

Player::Player(b2World& world,
               float positionX,
               float positionY, 
               std::vector<std::unique_ptr<Updatable>>& updatables,
               std::vector<const Renderable*>& renderables,
               std::vector<Physical*>& physicalUpdatables,
               Camera& camera)
               : Character(world, positionX, positionY, updatables, renderables, physicalUpdatables),
               m_camera(camera)
{
    m_characterRectangleShape.setFillColor(sf::Color::Red);
    isAPlayer = true;
}

void Player::update(const float deltaTime, UpdateParameters& updateParameters) {
    Character::update(deltaTime, updateParameters);
    m_camera.getView()->setCenter(m_characterRectangleShape.getPosition());
}

void Player::physicsUpdate(const float physicsTimeStep, UpdateParameters& updateParameters)
{   
    float horizontalMovement = 0.f;
    float verticalMovement = 0.f;
    float rotationalMovement = 0.f;

    if (updateParameters.keyboardAndMouseState.getKeyPressed(KeyboardAndMouseState::KeyName::moveLeft)) {
        horizontalMovement -= 1.f;
    }
    if (updateParameters.keyboardAndMouseState.getKeyPressed(KeyboardAndMouseState::KeyName::moveRight)) {
        horizontalMovement += 1.f;
    }
    if (updateParameters.keyboardAndMouseState.getKeyPressed(KeyboardAndMouseState::KeyName::moveDown)) {
        verticalMovement += 1.f;
    }
    if (updateParameters.keyboardAndMouseState.getKeyPressed(KeyboardAndMouseState::KeyName::moveUp)) {
        verticalMovement -= 1.f;
    }
    if (updateParameters.keyboardAndMouseState.getKeyPressed(KeyboardAndMouseState::KeyName::rotateClockwise)) {
        rotationalMovement += 1.f;
    }
    if (updateParameters.keyboardAndMouseState.getKeyPressed(KeyboardAndMouseState::KeyName::rotateCounterClockwise)) {
        rotationalMovement -= 1.f;
    }

    if (updateParameters.keyboardAndMouseState.getKeyPressed(KeyboardAndMouseState::KeyName::use) == true && m_useKeyAlreadyPressed == false)
    {
        if (m_rightHandJoint != nullptr) {
            Player::releaseRightHandJoin();
            m_useKeyAlreadyPressed = true;
        }
        else if (m_rightHandJoint == nullptr) {
            if (!updateParameters.grabables.empty()) {
                auto worldPoint = m_rigidBody->GetWorldCenter();
                auto grabables = updateParameters.grabables;
                auto sortByClosestToPlayer = [worldPoint](const Grabable* grabableA, const Grabable* grabableB) {return b2Distance(worldPoint, grabableA->getB2Body()->GetWorldCenter()) < b2Distance(worldPoint, grabableB->getB2Body()->GetWorldCenter()); };
                auto closestToPlayer = *std::min_element(grabables.begin(), grabables.end(), sortByClosestToPlayer);
                const Grabable* grabbed = closestToPlayer;
                if (b2Distance(grabbed->getB2Body()->GetWorldCenter(), m_rigidBody->GetWorldCenter()) < 1.f) {
                    joinRightHand(grabbed);
                }
            }
            m_useKeyAlreadyPressed = true;
        }
    }

    if (updateParameters.keyboardAndMouseState.mouseRight == true)
    {
        if (m_rightHandJoint != nullptr) {
            sf::Vector2f sfmlDifference = { updateParameters.window.mapPixelToCoords(
                                       updateParameters.keyboardAndMouseState.currentMousePosition) -
                                       updateParameters.window.mapPixelToCoords(
                                       updateParameters.keyboardAndMouseState.mousePositionInWindowWhenRightOrMiddleMouseButtonPressedDelta) };
            float difference = static_cast<float>( (std::sqrt(std::pow(sfmlDifference.x, 2) + std::pow(sfmlDifference.y, 2)))) * physicsTimeStep;
            if (sfmlDifference.x < 0.f) {
                difference = -difference;
            }
            m_rightHandJoint->GetBodyB()->ApplyAngularImpulse(difference, true);
        }
    }

    else if (updateParameters.keyboardAndMouseState.getKeyPressed(KeyboardAndMouseState::KeyName::use) == false && m_useKeyAlreadyPressed == true) {
        m_useKeyAlreadyPressed = false;
    }

    b2Vec2 forceToMoveBy = { horizontalMovement * m_moveSpeedMultiplier * physicsTimeStep, verticalMovement * m_moveSpeedMultiplier * physicsTimeStep };
    float forceToRotateBy = rotationalMovement * m_rotationSpeedMultiplier * physicsTimeStep;

    b2Vec2 vel = m_rigidBody->GetLinearVelocity();

    m_rigidBody->ApplyForceToCenter(forceToMoveBy, true);
    m_rigidBody->ApplyAngularImpulse(forceToRotateBy, true);
}