#pragma once

#include "Weapon.h"

class Spear : public Weapon
{
public:
    Spear(b2World& world,
        float positionX,
        float positionY,
        std::vector<std::unique_ptr<Updatable>>& updatables,
        std::vector<const Renderable*>& renderables,
        std::vector<const Grabable*>& grabables);

    virtual ~Spear() = default;

    void update(const float deltaTime, UpdateParameters& updateParameters) override;

    const sf::Drawable* getDrawable() const override;

    void render(sf::RenderWindow& drawingWindow) const override;

    b2Body* getB2Body() const override;

protected:

    float m_shaftDensityMultiplier = 20.f;
    float m_spearHeadDensityMultiplier = 20.f;

    // In Metres
    float m_shaftWidth = 0.03f;
    float m_shaftHeight = 2.f;
    float m_initialRenderZLevel = 1.25f;

    bool m_usingPhysics = true;

    //defines the shape and the location of the fixture
    b2Vec2 m_spearHeadShape[8] = {
                                 {0.f, 0.f + (m_shaftHeight / 2.f)}, // bottom middle
                                 {0.0175f, 0.f + (m_shaftHeight / 2.f)}, // bottom right
                                 {0.035f, 0.18f + (m_shaftHeight / 2.f)}, // lowermiddle right
                                 {0.0175f, 0.48f + (m_shaftHeight / 2.f)}, // uppermiddle right
                                 {0.f, 0.53f + (m_shaftHeight / 2.f)}, // top middle
                                 {-0.0175f, 0.48f + (m_shaftHeight / 2.f)}, // uppermiddle left
                                 {-0.035f, 0.18f + (m_shaftHeight / 2.f)}, // lowermiddle left
                                 {-0.0175f, 0.f + (m_shaftHeight / 2.f)} // bottom left
    };

    b2PolygonShape m_shaftPolygonShape;
    b2FixtureDef m_shaftFixtureDef;

    b2PolygonShape m_spearHeadPolygonShape;
    b2FixtureDef m_spearHeadFixtureDef;

    b2BodyDef m_spearRigidBodyDef;
    b2Body* m_spearRigidBody = nullptr;

    bool m_beingRendered = true;
    sf::RectangleShape m_shaftRectangleShape;
    sf::ConvexShape m_spearHeadConvexShape;
};