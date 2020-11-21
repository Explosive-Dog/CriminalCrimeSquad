#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "Updatable.h"
#include "Renderable.h"


class Character : public Updatable, public Renderable
{

public:

    Character(b2World &world, float positionX, float positionY);

    virtual ~Character() = default;

    const sf::Drawable* getDrawable() const;

    const unsigned int getRenderPriority() const;

    void setPlayerControlled(bool trueOrFalse);

    bool playerControlled();

    virtual void update(const float deltaTime, UpdateParameters& updateParameters);

private:

    bool m_playerControlled = false;

    std::string m_firstName = "Firstname";
    std::string m_lastName = "Lastname";
    float m_hp = 1000.f;

    // In Kilograms
    float m_weight = 65.f;

    // In Millimetres
    float m_shoulderWidth = 440.f;
    float m_chestSize = 110.f;

    float m_moveSpeed = 10000000.f;

    bool m_usingPhysics = true;
    b2BodyDef m_rigidBodyDef;
    b2Body* m_rigidBody;
    b2PolygonShape m_dynamicBox;
    b2FixtureDef m_fixtureDef;

    bool m_beingRendered = true;
    unsigned int m_renderPriority = 10;
    sf::RectangleShape m_characterRectangleShape;

};

