#pragma once

#include "Weapon.h"

class Sword : public Weapon
{
public:
    Sword(b2World& world,
        float positionX,
        float positionY,
        std::vector<std::unique_ptr<Updatable>>& updatables,
        std::vector<const Renderable*>& renderables,
        std::vector<const Grabable*>& grabables);

    virtual ~Sword() = default;

    void update(const float deltaTime, UpdateParameters& updateParameters) override;

    const sf::Drawable* getDrawable() const override;

    void render(sf::RenderWindow& drawingWindow) const override;

    b2Body* getB2Body() const override;

protected:

    float m_gripDensityMultiplier = 10.f;
    float m_bladeDensityMultiplier = 15.f;

    // In Metres
    float m_gripWidth = 0.03f;
    float m_gripHeight = 0.1365f;

    float m_guardWidth = 0.1937f;
    float m_guardHeight = 0.011f;

    float m_pomelRadius = 0.0191f;

    float m_initialRenderZLevel = 1.25f;

    bool m_usingPhysics = true;

    b2CircleShape m_pomelbox2dCircleShape;
    b2FixtureDef m_pomelFixtureDef;

    b2PolygonShape m_guardPolygonShape;
    b2FixtureDef m_guardFixtureDef;

    b2PolygonShape m_gripPolygonShape;
    b2FixtureDef m_gripFixtureDef;

    //defines the shape and the location of the fixture
    b2Vec2 m_bladeShape[6] = {
                         {0.f, 0.f + (m_gripHeight / 2.f)}, // bottom middle
                         {0.0225f, 0.f + (m_gripHeight / 2.f)}, // bottom right
                         {0.0096f, 0.83f + (m_gripHeight / 2.f)}, // uppermiddle right
                         {0.f, 0.8541f + (m_gripHeight / 2.f)}, // top middle
                         {-0.0096f, 0.83f + (m_gripHeight / 2.f)}, // uppermiddle left
                         {-0.0225f, 0.f + (m_gripHeight / 2.f)} // bottom left
    };

    b2PolygonShape m_bladePolygonShape;
    b2FixtureDef m_bladeFixtureDef;

    b2BodyDef m_swordRigidBodyDef;
    b2Body* m_swordRigidBody;

    bool m_beingRendered = true;
    sf::RectangleShape m_gripRectangleShape;
    sf::ConvexShape m_bladeConvexShape;
    sf::RectangleShape m_guardRectangleShape;
    sf::CircleShape m_pomelCircleShape;
};