#include "Sword.h"

Sword::Sword(b2World& world,
    float positionX,
    float positionY,
    std::vector<std::unique_ptr<Updatable>>& updatables,
    std::vector<const Renderable*>& renderables,
    std::vector<const Grabable*>& grabables)
    : Weapon(grabables)
{
    m_swordRigidBodyDef.type = b2_dynamicBody;
    m_swordRigidBodyDef.position.Set(positionX, positionY);
    m_swordRigidBodyDef.linearDamping = 2.f;
    m_swordRigidBodyDef.angularDamping = 2.f;

    m_gripPolygonShape.SetAsBox(m_gripWidth / 2.f, m_gripHeight / 2.f);
    m_gripFixtureDef.shape = &m_gripPolygonShape;
    m_gripFixtureDef.density = m_gripDensityMultiplier;
    m_gripFixtureDef.friction = 1.f;

    m_guardPolygonShape.SetAsBox(m_guardWidth / 2.f, m_guardHeight / 2.f, {0.f, m_gripHeight / 2.f}, 0.f);
    m_guardFixtureDef.shape = &m_guardPolygonShape;
    m_guardFixtureDef.density = m_bladeDensityMultiplier;
    m_guardFixtureDef.friction = 1.f;

    m_pomelbox2dCircleShape.m_p.Set(0.f, -m_gripHeight / 2.f + m_pomelRadius);
    m_pomelbox2dCircleShape.m_radius = m_pomelRadius;
    m_pomelFixtureDef.shape = &m_pomelbox2dCircleShape;
    m_pomelFixtureDef.density = m_bladeDensityMultiplier;
    m_pomelFixtureDef.friction = 1.f;

    int bladeShapeAmountOfGeometryPoints = static_cast<int>(std::size(m_bladeShape));
    m_bladePolygonShape.Set(m_bladeShape, bladeShapeAmountOfGeometryPoints);
    m_bladeFixtureDef.shape = &m_bladePolygonShape;
    m_bladeFixtureDef.density = m_bladeDensityMultiplier;
    m_bladeFixtureDef.friction = 2.f;

    m_swordRigidBody = world.CreateBody(&m_swordRigidBodyDef);
    m_swordRigidBody->CreateFixture(&m_gripFixtureDef);
    m_swordRigidBody->CreateFixture(&m_bladeFixtureDef);
    m_swordRigidBody->CreateFixture(&m_guardFixtureDef);
    m_swordRigidBody->CreateFixture(&m_pomelFixtureDef);

    m_gripRectangleShape.setFillColor(sf::Color(86, 64, 45, 255));
    m_gripRectangleShape.setSize({ m_gripWidth, m_gripHeight });
    m_gripRectangleShape.setOrigin(m_gripWidth / 2.f, m_gripHeight / 2.f);
    m_gripRectangleShape.setPosition(positionX, positionY);
    m_gripRectangleShape.setRotation(m_swordRigidBody->GetAngle() * (180.f / b2_pi));

    m_bladeConvexShape.setFillColor(sf::Color(155, 155, 155, 255));
    m_bladeConvexShape.setPointCount(bladeShapeAmountOfGeometryPoints);
    for (size_t i = 0; i < bladeShapeAmountOfGeometryPoints; ++i) {
        m_bladeConvexShape.setPoint(i, sf::Vector2f(m_bladeShape[i].x, m_bladeShape[i].y));
    }
    m_bladeConvexShape.setPosition(positionX, positionY);
    m_bladeConvexShape.setRotation(m_swordRigidBody->GetAngle() * (180.f / b2_pi));

    m_guardRectangleShape.setFillColor(sf::Color(155, 155, 155, 255));
    m_guardRectangleShape.setSize({ m_guardWidth, m_guardHeight });
    m_guardRectangleShape.setOrigin(m_guardWidth / 2.f, -m_gripHeight / 2.f);
    m_guardRectangleShape.setPosition(positionX, positionY);
    m_guardRectangleShape.setRotation(m_swordRigidBody->GetAngle() * (180.f / b2_pi));

    m_pomelCircleShape.setFillColor(sf::Color(155, 155, 155, 255));
    m_pomelCircleShape.setRadius(m_pomelRadius);
    m_pomelCircleShape.setOrigin(m_pomelRadius, m_gripHeight / 2.f + m_pomelRadius);
    m_pomelCircleShape.setPosition(positionX, positionY);
    m_pomelCircleShape.setRotation(m_swordRigidBody->GetAngle() * (180.f / b2_pi));

    m_renderZLevel = m_initialRenderZLevel;

    m_swordRigidBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(nullptr);
    updatables.emplace_back(this);
    renderables.push_back(this);
    grabables.push_back(this);
}
void Sword::update(const float deltaTime, UpdateParameters& updateParameters)
{
    (void)updateParameters;
    (void)deltaTime;

    m_gripRectangleShape.setPosition(m_swordRigidBody->GetPosition().x, m_swordRigidBody->GetPosition().y);
    m_gripRectangleShape.setRotation(m_swordRigidBody->GetAngle() * (180.f / b2_pi));
    m_bladeConvexShape.setPosition(m_swordRigidBody->GetPosition().x, m_swordRigidBody->GetPosition().y);
    m_bladeConvexShape.setRotation(m_swordRigidBody->GetAngle() * (180.f / b2_pi));
    m_guardRectangleShape.setPosition(m_swordRigidBody->GetPosition().x, m_swordRigidBody->GetPosition().y);
    m_guardRectangleShape.setRotation(m_swordRigidBody->GetAngle() * (180.f / b2_pi));
    m_pomelCircleShape.setPosition(m_swordRigidBody->GetPosition().x, m_swordRigidBody->GetPosition().y);
    m_pomelCircleShape.setRotation(m_swordRigidBody->GetAngle() * (180.f / b2_pi));
}

const sf::Drawable* Sword::getDrawable() const
{
    return &m_gripRectangleShape;
}

void Sword::render(sf::RenderWindow& drawingWindow) const
{
    drawingWindow.draw(m_gripRectangleShape);
    drawingWindow.draw(m_bladeConvexShape);
    drawingWindow.draw(m_guardRectangleShape);
    drawingWindow.draw(m_pomelCircleShape);
}

b2Body* Sword::getB2Body() const {
    return m_swordRigidBody;
}