#include "Character.h"

#include <iostream>


Character::Character(b2World &world, float positionX, float positionY) {

    m_rigidBodyDef.type = b2_dynamicBody;
    m_rigidBodyDef.position.Set(positionX, positionY);
    m_rigidBody = world.CreateBody(&m_rigidBodyDef);
    m_dynamicBox.SetAsBox(m_shoulderWidth / 2.f, m_chestSize / 2.f);
    m_fixtureDef.shape = &m_dynamicBox;
    m_fixtureDef.density = m_weight;
    m_fixtureDef.friction = 1.f;
    m_rigidBody->CreateFixture(&m_fixtureDef);
    
    m_characterRectangleShape.setFillColor(sf::Color::White);
    m_characterRectangleShape.setSize({ m_shoulderWidth, m_chestSize });
    m_characterRectangleShape.setOrigin(m_shoulderWidth / 2.f, m_chestSize / 2.f);
    m_characterRectangleShape.setPosition(positionX, positionY);
    m_characterRectangleShape.setRotation(m_rigidBody->GetAngle() * (180.f / b2_pi));       
    
}

const sf::Drawable* Character::getDrawable() const
{
    return &m_characterRectangleShape;
}

const unsigned int Character::getRenderPriority() const
{
    return m_renderPriority;
}

void Character::setPlayerControlled(bool trueOrFalse)
{
    m_playerControlled = trueOrFalse;
}

bool Character::playerControlled()
{
    return m_playerControlled;
}

void Character::update(const float deltaTime,
    const sf::RenderWindow& window,
    sf::View& view, KeyboardAndMouseState& keyboardAndMouseState,
    std::vector<const Collidable*>& vectorOfCollidables,
    std::vector<Selectable*>& vectorOfSelectables)
{
    m_characterRectangleShape.setPosition(m_rigidBody->GetPosition().x, m_rigidBody->GetPosition().y);
    m_characterRectangleShape.setRotation(m_rigidBody->GetAngle() * (180.f / b2_pi));

    if (playerControlled()) {
        m_characterRectangleShape.setFillColor(sf::Color::Red);

        if (keyboardAndMouseState.verticalBeingPressed == false) {
            keyboardAndMouseState.vertical /= 2.f;
        }

        if (keyboardAndMouseState.horizontalBeingPressed == false) {
            keyboardAndMouseState.horizontal /= 2.f;
        }

        b2Vec2 forceToMoveBy = { keyboardAndMouseState.horizontal * m_moveSpeed , -keyboardAndMouseState.vertical * m_moveSpeed };
        std::cout << "X: " << keyboardAndMouseState.horizontal << std::endl;
        std::cout << "Y: " << keyboardAndMouseState.vertical << std::endl;
        // m_rigidBody->SetLinearVelocity(forceToMoveBy);



        b2Vec2 vel = m_rigidBody->GetLinearVelocity();
        m_rigidBody->ApplyForceToCenter (forceToMoveBy, true);
    }
}