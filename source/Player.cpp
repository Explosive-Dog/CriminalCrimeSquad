#include "Player.h"
#include <iostream>

Player::Player(b2World& world, float positionX, float positionY, Camera& camera)
    : Character(world, positionX, positionY), m_camera(camera) {
    
}

void Player::update(const float deltaTime, UpdateParameters& updateParameters) {

    Character::update(deltaTime, updateParameters);

    m_characterRectangleShape.setFillColor(sf::Color::Red);

    float horizontalMovement = 0.f;
    float verticalMovement = 0.f;
    float rotationalMovement = 0.f;

    if (updateParameters.keyboardAndMouseState.moveLeftKeyPressed) {
        horizontalMovement -= 1.f;
    }
    if (updateParameters.keyboardAndMouseState.moveRightKeyPressed) {
        horizontalMovement += 1.f;
    }
    if (updateParameters.keyboardAndMouseState.moveDownKeyPressed) {
        verticalMovement -= 1.f;
    }
    if (updateParameters.keyboardAndMouseState.moveUpKeyPressed) {
        verticalMovement += 1.f;
    }
    if (updateParameters.keyboardAndMouseState.rotateClockwise) {
        rotationalMovement -= 1.f;
    }
    if (updateParameters.keyboardAndMouseState.rotateCounterClockwise) {
        rotationalMovement += 1.f;
    }

    b2Vec2 forceToMoveBy = { horizontalMovement * m_moveSpeedMultiplier , verticalMovement * m_moveSpeedMultiplier };
    float forceToRotateBy = rotationalMovement * m_rotationSpeedMultiplier;

    std::cout << "X: " << updateParameters.keyboardAndMouseState.horizontal << std::endl;
    std::cout << "Y: " << updateParameters.keyboardAndMouseState.vertical << std::endl;
    std::cout << m_rigidBody->GetMass() << std::endl;
    std::cout << "A: " << updateParameters.keyboardAndMouseState.moveLeftKeyPressed <<
        " S: " << updateParameters.keyboardAndMouseState.moveDownKeyPressed <<
        " D: " << updateParameters.keyboardAndMouseState.moveRightKeyPressed <<
        " W: " << updateParameters.keyboardAndMouseState.moveUpKeyPressed << std::endl;
    // m_rigidBody->SetLinearVelocity(forceToMoveBy);
    b2Vec2 vel = m_rigidBody->GetLinearVelocity();

    //std::cout << "VEL X: " << vel.x << std::endl;
    //std::cout << "VEL Y: " << vel.y << std::endl;

    m_rigidBody->ApplyForceToCenter(forceToMoveBy, true);
    m_rigidBody->ApplyAngularImpulse(forceToRotateBy, true);
    m_camera.getView()->setCenter(m_characterRectangleShape.getPosition());
}