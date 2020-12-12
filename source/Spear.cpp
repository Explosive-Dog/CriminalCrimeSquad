#include "Spear.h"

Spear::Spear(b2World& world,
    float positionX,
    float positionY,
    std::vector<std::unique_ptr<Updatable>>& updatables,
    std::vector<const Renderable*>& renderables,
    std::vector<const Grabable*>& grabables)
    : Weapon(grabables)
{
    m_spearRigidBodyDef.type = b2_dynamicBody;
    m_spearRigidBodyDef.position.Set(positionX, positionY);
    m_spearRigidBodyDef.linearDamping = 2.f;
    m_spearRigidBodyDef.angularDamping = 2.f;

    m_shaftPolygonShape.SetAsBox(m_shaftWidth / 2.f, m_shaftHeight / 2.f);
    m_shaftFixtureDef.shape = &m_shaftPolygonShape;
    m_shaftFixtureDef.density = m_shaftDensityMultiplier;
    m_shaftFixtureDef.friction = 1.f;

    int spearHeadShapeAmountOfGeometryPoints = static_cast<int>(std::size(m_spearHeadShape));
    m_spearHeadPolygonShape.Set(m_spearHeadShape, spearHeadShapeAmountOfGeometryPoints);
    m_spearHeadFixtureDef.shape = &m_spearHeadPolygonShape;
    m_spearHeadFixtureDef.density = m_spearHeadDensityMultiplier;
    m_spearHeadFixtureDef.friction = 2.f;

    m_spearRigidBody = world.CreateBody(&m_spearRigidBodyDef);
    m_spearRigidBody->CreateFixture(&m_shaftFixtureDef);
    m_spearRigidBody->CreateFixture(&m_spearHeadFixtureDef);

    m_shaftRectangleShape.setFillColor(sf::Color(86, 64, 45, 255));
    m_shaftRectangleShape.setSize({ m_shaftWidth, m_shaftHeight });
    m_shaftRectangleShape.setOrigin(m_shaftWidth / 2.f, m_shaftHeight / 2.f);
    m_shaftRectangleShape.setPosition(positionX, positionY);
    m_shaftRectangleShape.setRotation(m_spearRigidBody->GetAngle() * (180.f / b2_pi));

    m_spearHeadConvexShape.setFillColor(sf::Color(155, 155, 155, 255));
    m_spearHeadConvexShape.setPointCount(spearHeadShapeAmountOfGeometryPoints);
    for (size_t i = 0; i < spearHeadShapeAmountOfGeometryPoints; ++i) {
        m_spearHeadConvexShape.setPoint(i, sf::Vector2f(m_spearHeadShape[i].x, m_spearHeadShape[i].y));
    }
    m_spearHeadConvexShape.setPosition(positionX, positionY);
    m_spearHeadConvexShape.setRotation(m_spearRigidBody->GetAngle() * (180.f / b2_pi));

    m_renderZLevel = m_initialRenderZLevel;

    updatables.emplace_back(this);
    renderables.push_back(this);
    grabables.push_back(this);
}
void Spear::update(const float deltaTime, UpdateParameters& updateParameters)
{
    (void)updateParameters;
    (void)deltaTime;


    m_shaftRectangleShape.setPosition(m_spearRigidBody->GetPosition().x, m_spearRigidBody->GetPosition().y);
    m_shaftRectangleShape.setRotation(m_spearRigidBody->GetAngle() * (180.f / b2_pi));
    m_spearHeadConvexShape.setPosition(m_spearRigidBody->GetPosition().x, m_spearRigidBody->GetPosition().y);
    m_spearHeadConvexShape.setRotation(m_spearRigidBody->GetAngle() * (180.f / b2_pi));
}

const sf::Drawable* Spear::getDrawable() const
{
    return &m_shaftRectangleShape;
}

void Spear::render(sf::RenderWindow& drawingWindow) const
{
    drawingWindow.draw(m_shaftRectangleShape);
    drawingWindow.draw(m_spearHeadConvexShape);
}

b2Body* Spear::getB2Body() const {
    return m_spearRigidBody;
}