#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "Joinable.h"
#include "Physical.h"
#include "Renderable.h"
#include "Updatable.h"

class Character : public Updatable, public Renderable, public Joinable
{
public:
    Character(b2World &world,
              float positionX,
              float positionY, 
              std::vector<std::unique_ptr<Updatable>>& updatables,
              std::vector<const Renderable*>& renderables);

    virtual ~Character() = default;

    const sf::Drawable* getDrawable() const;

    void update(const float deltaTime, UpdateParameters& updateParameters) override;

    b2Body* getB2Body() const override;

    void joinRightHand(const Grabable* joiningBody);

    void releaseRightHandJoin();

    void render(sf::RenderWindow& drawingWindow) const override;

protected:

    std::string m_firstName = "Firstname";
    std::string m_lastName = "Lastname";
    float m_hp = 1000.f;

    float m_densityMultiplier = 1000.f;

    // In Metres
    float m_shoulderWidth = 0.44f;
    float m_chestSize = 0.15f;
    float m_initialRenderZLevel = 2.f;

    float m_moveSpeedMultiplier = 100000.f;
    float m_rotationSpeedMultiplier = 20.f;

    bool m_usingPhysics = true;
    b2BodyDef m_rigidBodyDef;
    b2Body* m_rigidBody = nullptr;
    b2PolygonShape m_dynamicBox;
    b2FixtureDef m_fixtureDef;

    bool m_beingRendered = true;
    sf::RectangleShape m_characterRectangleShape;

    const Grabable* m_rightHandIsGrabbing = nullptr;
    b2Joint* m_rightHandJoint = nullptr;
    b2RevoluteJointDef m_rightHandJointDef;

    const Grabable* m_leftHandIsGrabbing = nullptr;
    b2Joint* m_leftHandJoint = nullptr;
    b2RevoluteJointDef m_leftHandJointDef;

    bool dead = false;
    bool removalFlag = false;
    sf::Clock* deadTimer = nullptr;
};