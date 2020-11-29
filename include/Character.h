#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "Joinable.h"
#include "Updatable.h"
#include "Renderable.h"


class Character : public Updatable, public Renderable, public Joinable
{

public:

    Character(b2World &world, float positionX, float positionY);

    virtual ~Character() = default;

    const sf::Drawable* getDrawable() const;

    void update(const float deltaTime, UpdateParameters& updateParameters) override;

    b2Body* getB2Body() override;

protected:

    std::string m_firstName = "Firstname";
    std::string m_lastName = "Lastname";
    float m_hp = 1000.f;

    float m_densityMultiplier = 1000.f;

    // In Metres
    float m_shoulderWidth = 0.44f;
    float m_chestSize = 0.15f;
    float m_initialRenderZLevel = 2.f;

    float m_moveSpeedMultiplier = 1000.f;
    float m_rotationSpeedMultiplier = 1.f;

    bool m_usingPhysics = true;
    b2BodyDef m_rigidBodyDef;
    b2Body* m_rigidBody;
    b2PolygonShape m_dynamicBox;
    b2FixtureDef m_fixtureDef;

    bool m_beingRendered = true;
    sf::RectangleShape m_characterRectangleShape;

};

