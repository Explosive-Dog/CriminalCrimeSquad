#include "Spear.h"

Spear::Spear(b2World& world,
    float positionX,
    float positionY,
    std::vector<std::unique_ptr<Updatable>>& updatables,
    std::vector<const Renderable*>& renderables,
    std::vector<const Grabable*>& grabables)
    : Weapon(grabables)
{
    m_rigidBodyDef.type = b2_dynamicBody;
    m_rigidBodyDef.position.Set(positionX, positionY);
    m_rigidBodyDef.linearDamping = 2.f;
    m_rigidBodyDef.angularDamping = 2.f;
    m_rigidBody = world.CreateBody(&m_rigidBodyDef);

    m_dynamicBox.SetAsBox(m_shaftWidth / 2.f, m_shaftHeight / 2.f);
    m_fixtureDef.shape = &m_dynamicBox;
    m_fixtureDef.density = m_densityMultiplier;
    m_fixtureDef.friction = 1.f;
    m_rigidBody->CreateFixture(&m_fixtureDef);

    m_shaftRectangleShape.setFillColor(sf::Color(86, 64, 45, 255));
    m_shaftRectangleShape.setSize({ m_shaftWidth, m_shaftHeight });
    m_shaftRectangleShape.setOrigin(m_shaftWidth / 2.f, m_shaftHeight / 2.f);
    m_shaftRectangleShape.setPosition(positionX, positionY);
    m_shaftRectangleShape.setRotation(m_rigidBody->GetAngle() * (180.f / b2_pi));






    m_renderZLevel = m_initialRenderZLevel;

    updatables.emplace_back(this);
    renderables.push_back(this);
    grabables.push_back(this);
}
void Spear::update(const float deltaTime, UpdateParameters& updateParameters)
{
    (void)updateParameters;
    (void)deltaTime;
    m_shaftRectangleShape.setPosition(m_rigidBody->GetPosition().x, m_rigidBody->GetPosition().y);
    m_shaftRectangleShape.setRotation(m_rigidBody->GetAngle() * (180.f / b2_pi));
}

const sf::Drawable* Spear::getDrawable() const
{
    return &m_shaftRectangleShape;
}

void Spear::render(sf::RenderWindow& drawingWindow) const
{
    drawingWindow.draw(m_shaftRectangleShape);
    drawingWindow.draw(m_spearHeadRectangleShape);
}

b2Body* Spear::getB2Body() const {
    return m_rigidBody;
}