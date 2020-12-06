#pragma once

#include "Weapon.h"

class QuaterStaff : public Weapon
{
public:
    QuaterStaff(b2World& world,
        float positionX,
        float positionY,
        std::vector<std::unique_ptr<Updatable>>& updatables,
        std::vector<const Renderable*>& renderables,
        std::vector<const Grabable*>& grabables);

    virtual ~QuaterStaff() = default;

    void update(const float deltaTime, UpdateParameters& updateParameters) override;

    const sf::Drawable* getDrawable() const override;

    b2Body* getB2Body() const override;

protected:

    float m_densityMultiplier = 20.f;

    // In Metres
    float m_staffWidth = 0.03f;
    float m_staffHeight = 2.f;
    float m_initialRenderZLevel = 1.25f;

    bool m_usingPhysics = true;
    b2BodyDef m_rigidBodyDef;
    b2Body* m_rigidBody;
    b2PolygonShape m_dynamicBox;
    b2FixtureDef m_fixtureDef;

    bool m_beingRendered = true;

    sf::RectangleShape m_characterRectangleShape;
};