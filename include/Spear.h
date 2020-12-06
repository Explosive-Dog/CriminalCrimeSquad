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

    b2Body* getB2Body() const override;

protected:

    float m_densityMultiplier = 20.f;

    // In Metres
    float m_shaftWidth = 0.03f;
    float m_shaftHeight = 2.f;
    float m_initialRenderZLevel = 1.25f;

    float m_spearHeadHeight = 0.f;
    float m_spearHeadWidth = 0.f;

    bool m_usingPhysics = true;
    b2BodyDef m_rigidBodyDef;
    b2Body* m_rigidBody;
    b2PolygonShape m_dynamicBox;
    b2FixtureDef m_fixtureDef;

    bool m_beingRendered = true;

    sf::RectangleShape m_characterRectangleShape;
};