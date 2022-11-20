#pragma once
#include <SFML/Graphics.hpp>

#include "Renderable.h"
#include "Updatable.h"

class Character : public Updatable, public Renderable
{
public:
    Character(float positionX,
              float positionY, 
              std::vector<std::unique_ptr<Updatable>>& updatables,
              std::vector<const Renderable*>& renderables);

    virtual ~Character() = default;

    const sf::Drawable* getDrawable() const;

    void update(const float deltaTime, UpdateParameters& updateParameters) override;

    void render(sf::RenderWindow& drawingWindow) const override;

protected:

    bool isAPlayer = false;

    std::string m_firstName = "Firstname";
    std::string m_lastName = "Lastname";
    float m_hp = 10.f;
    bool m_dead = false;
    bool m_deadTimerSet = false;
    bool m_removalFlag = false;
    std::unique_ptr<sf::Clock> m_deadTimer = nullptr;

    float m_densityMultiplier = 1000.f;

    // In Metres
    float m_shoulderWidth = 0.44f;
    float m_chestSize = 0.15f;
    float m_initialRenderZLevel = 2.f;

    float m_moveSpeedMultiplier = 100000.f;
    float m_rotationSpeedMultiplier = 20.f;

    bool m_beingRendered = true;
    sf::RectangleShape m_characterRectangleShape;

};