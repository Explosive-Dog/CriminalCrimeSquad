#include "Character.h"

Character::Character(b2World &world,
                    float positionX,
                    float positionY,
                    std::vector<std::unique_ptr<Updatable>>& updatables,
                    std::vector<const Renderable*>& renderables) 
{
    m_rigidBodyDef.type = b2_dynamicBody;
    m_rigidBodyDef.position.Set(positionX, positionY);
    m_rigidBodyDef.linearDamping = 2.f;
    m_rigidBodyDef.angularDamping = 2.f;
    m_rigidBody = world.CreateBody(&m_rigidBodyDef);

    m_dynamicBox.SetAsBox(m_shoulderWidth / 2.f, m_chestSize / 2.f);
    m_fixtureDef.shape = &m_dynamicBox;
    m_fixtureDef.density = m_densityMultiplier;
    m_fixtureDef.friction = 0.4f;
    m_rigidBody->CreateFixture(&m_fixtureDef);
    
    m_characterRectangleShape.setFillColor(sf::Color::White);
    m_characterRectangleShape.setSize({ m_shoulderWidth, m_chestSize });
    m_characterRectangleShape.setOrigin(m_shoulderWidth / 2.f, m_chestSize / 2.f);
    m_characterRectangleShape.setPosition(positionX, positionY);
    m_characterRectangleShape.setRotation(m_rigidBody->GetAngle() * (180.f / b2_pi));

    m_renderZLevel = m_initialRenderZLevel;
    
    updatables.emplace_back(this);
    renderables.push_back(this);
}

const sf::Drawable* Character::getDrawable() const
{
    return &m_characterRectangleShape;
}

void Character::update(const float deltaTime, UpdateParameters& updateParameters)
{
    (void)deltaTime;
    (void)updateParameters;
    m_characterRectangleShape.setPosition(m_rigidBody->GetPosition().x, m_rigidBody->GetPosition().y);
    m_characterRectangleShape.setRotation(m_rigidBody->GetAngle() * (180.f / b2_pi));

    if (dead) {
        m_characterRectangleShape.setFillColor(sf::Color::Green);
        deadTimer = new sf::Clock;
        deadTimer->restart();
    }
    if (deadTimer != nullptr) {
        if (deadTimer->getElapsedTime().asSeconds() > 10.f) {
            removalFlag = true;
        }
    }
}

b2Body* Character::getB2Body() const {
    return m_rigidBody;
}

void Character::joinRightHand(const Grabable* joiningBody) 
{
    if (m_rightHandJoint == nullptr) {
        m_rightHandJointDef.bodyA = m_rigidBody;
        m_rightHandJointDef.bodyB = joiningBody->getB2Body();
        m_rightHandIsGrabbing = joiningBody;
        m_rightHandJointDef.collideConnected = false;
        m_rightHandJoint = m_rigidBody->GetWorld()->CreateJoint(&m_rightHandJointDef);
        m_rightHandIsGrabbing->objectGrabbed();
    }
}

void Character::releaseRightHandJoin()
{
    if (m_rightHandJoint != nullptr) {
        m_rightHandIsGrabbing->objectReleased();
        m_rightHandIsGrabbing = nullptr;
        m_rigidBody->GetWorld()->DestroyJoint(m_rightHandJoint);
        m_rightHandJoint = nullptr;
    }
}

void Character::render(sf::RenderWindow& drawingWindow) const
{
    drawingWindow.draw(m_characterRectangleShape);
}