#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "Joinable.h"
#include "Renderable.h"
#include "Updatable.h"

class Weapon : public Updatable, public Renderable, public Joinable
{
public:
	Weapon(b2World& world, float positionX, float positionY);

	virtual ~Weapon() = default;

	void update(const float deltaTime, UpdateParameters& updateParameters) override;

    const sf::Drawable* getDrawable() const override;

    b2Body* getB2Body() override;

protected:

    float m_densityMultiplier = 20.f;

    // In Metres
    float m_Width = 0.03f;
    float m_height = 2.f;
    float m_initialRenderZLevel = 1.25f;

    bool m_usingPhysics = true;
    b2BodyDef m_rigidBodyDef;
    b2Body* m_rigidBody;
    b2PolygonShape m_dynamicBox;
    b2FixtureDef m_fixtureDef;

    bool m_beingRendered = true;

    sf::RectangleShape m_characterRectangleShape;

};

