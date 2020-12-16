#include "QuaterStaff.h"

QuaterStaff::QuaterStaff(b2World& world,
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

    m_dynamicBox.SetAsBox(m_staffWidth / 2.f, m_staffHeight / 2.f);
    m_fixtureDef.shape = &m_dynamicBox;
    m_fixtureDef.density = m_densityMultiplier;
    m_fixtureDef.friction = 1.f;
    m_rigidBody->CreateFixture(&m_fixtureDef);

    m_quaterStaffRectangleShape.setFillColor(sf::Color(86, 64, 45, 255));
    m_quaterStaffRectangleShape.setSize({ m_staffWidth, m_staffHeight });
    m_quaterStaffRectangleShape.setOrigin(m_staffWidth / 2.f, m_staffHeight / 2.f);
    m_quaterStaffRectangleShape.setPosition(positionX, positionY);
    m_quaterStaffRectangleShape.setRotation(m_rigidBody->GetAngle() * (180.f / b2_pi));

    m_renderZLevel = m_initialRenderZLevel;

    m_rigidBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(nullptr);
    updatables.emplace_back(this);
    renderables.push_back(this);
    grabables.push_back(this);
}
void QuaterStaff::update(const float deltaTime, UpdateParameters& updateParameters)
{
    (void)updateParameters;
    (void)deltaTime;
    m_quaterStaffRectangleShape.setPosition(m_rigidBody->GetPosition().x, m_rigidBody->GetPosition().y);
    m_quaterStaffRectangleShape.setRotation(m_rigidBody->GetAngle() * (180.f / b2_pi));
}

const sf::Drawable* QuaterStaff::getDrawable() const
{
    return &m_quaterStaffRectangleShape;
}

void QuaterStaff::render(sf::RenderWindow& drawingWindow) const
{
    drawingWindow.draw(m_quaterStaffRectangleShape);
}

b2Body* QuaterStaff::getB2Body() const {
    return m_rigidBody;
}