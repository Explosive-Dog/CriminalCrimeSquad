#include "Player.h"

Player::Player(b2World& world, float positionX, float positionY, std::vector<std::unique_ptr<Updatable>>& updatables, std::vector<const Renderable*>& renderables, Camera& camera)
    : Character(world, positionX, positionY, updatables, renderables), m_camera(camera) {
}

void Player::update(const float deltaTime, UpdateParameters& updateParameters) {

    Character::update(deltaTime, updateParameters);

    m_characterRectangleShape.setFillColor(sf::Color::Red);

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
        if (m_rightHandJoined) {
            Player::releaseRightHandJoin(*m_rigidBody->GetWorld());
            m_useKeyAlreadyPressed = true;
        }
        else if (!m_rightHandJoined) {
            if (!updateParameters.grabables.empty()) {
                auto worldPoint = m_rigidBody->GetWorldCenter();
                auto grabables = updateParameters.grabables;
                auto sortByClosestToPlayer = [worldPoint](const Grabable* grabableA, const Grabable* grabableB) {return b2Distance(worldPoint, grabableA->getB2Body()->GetWorldCenter()) < b2Distance(worldPoint, grabableB->getB2Body()->GetWorldCenter()); };
                auto closestToPlayer = *std::min_element(grabables.begin(), grabables.end(), sortByClosestToPlayer);
                b2Body* grabbed = closestToPlayer->getB2Body();
                if (b2Distance(grabbed->GetWorldCenter(), m_rigidBody->GetWorldCenter()) < 1.f) {
                    joinRightHand(*m_rigidBody->GetWorld(), grabbed);
                }
            }
            m_useKeyAlreadyPressed = true;
        }
    }
    else if (updateParameters.keyboardAndMouseState.getKeyPressed(KeyboardAndMouseState::KeyName::use) == false && m_useKeyAlreadyPressed == true) {
        m_useKeyAlreadyPressed = false;
    }

    b2Vec2 forceToMoveBy = { horizontalMovement * m_moveSpeedMultiplier , verticalMovement * m_moveSpeedMultiplier };
    float forceToRotateBy = rotationalMovement * m_rotationSpeedMultiplier;

    b2Vec2 vel = m_rigidBody->GetLinearVelocity();

    m_rigidBody->ApplyForceToCenter(forceToMoveBy, true);
    m_rigidBody->ApplyAngularImpulse(forceToRotateBy, true);
    m_camera.getView()->setCenter(m_characterRectangleShape.getPosition());
}