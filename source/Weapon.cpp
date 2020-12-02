#include "Weapon.h"
//#include <iostream>

Weapon::Weapon(b2World& world,
    float positionX,
    float positionY,
    std::vector<std::unique_ptr<Updatable>>& updatables,
    std::vector<const Renderable*>& renderables,
    std::vector<const Grabable*>& grabables)
{
    m_rigidBodyDef.type = b2_dynamicBody;
    m_rigidBodyDef.position.Set(positionX, positionY);
    m_rigidBodyDef.linearDamping = 2.f;
    m_rigidBodyDef.angularDamping = 2.f;
    m_rigidBody = world.CreateBody(&m_rigidBodyDef);

    m_dynamicBox.SetAsBox(m_Width / 2.f, m_height / 2.f);
    m_fixtureDef.shape = &m_dynamicBox;
    m_fixtureDef.density = m_densityMultiplier;
    m_fixtureDef.friction = 1.f;
    m_rigidBody->CreateFixture(&m_fixtureDef);

    m_characterRectangleShape.setFillColor(sf::Color(86, 64, 45, 255));
    m_characterRectangleShape.setSize({ m_Width, m_height });
    m_characterRectangleShape.setOrigin(m_Width / 2.f, m_height / 2.f);
    m_characterRectangleShape.setPosition(positionX, positionY);
    m_characterRectangleShape.setRotation(m_rigidBody->GetAngle() * (180.f / b2_pi));

    m_renderZLevel = m_initialRenderZLevel;

    updatables.emplace_back(this);
    renderables.push_back(this);
    grabables.push_back(this);
}

void Weapon::update(const float deltaTime, UpdateParameters& updateParameters)
{
    m_characterRectangleShape.setPosition(m_rigidBody->GetPosition().x, m_rigidBody->GetPosition().y);
    m_characterRectangleShape.setRotation(m_rigidBody->GetAngle() * (180.f / b2_pi));
    //std::cout << "Weapon shaft weight" << m_rigidBody->GetMass() << std::endl;
}

const sf::Drawable* Weapon::getDrawable() const
{
    return &m_characterRectangleShape;
}

b2Body* Weapon::getB2Body() const {
    return m_rigidBody;
}