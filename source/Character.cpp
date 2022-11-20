#include "Character.h"

#include <cmath>
#include <iostream>

Character::Character(float positionX,
                    float positionY,
                    std::vector<std::unique_ptr<Updatable>>& updatables,
                    std::vector<const Renderable*>& renderables) 
{
 
    m_characterRectangleShape.setFillColor(sf::Color::White);
    m_characterRectangleShape.setSize({ m_shoulderWidth, m_chestSize });
    m_characterRectangleShape.setOrigin(m_shoulderWidth / 2.f, m_chestSize / 2.f);
    m_characterRectangleShape.setPosition(positionX, positionY);

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


    if (m_dead == true && m_deadTimerSet == false) {
        m_characterRectangleShape.setFillColor(sf::Color::Green);
        m_deadTimer = std::make_unique<sf::Clock>();
        m_deadTimerSet = true;
        m_deadTimer->restart();
    }
    if (m_deadTimer != nullptr && m_removalFlag == false) {
        if (m_deadTimer->getElapsedTime().asSeconds() > 10.f) {
            m_removalFlag = true;
            std::cout << "removing" << std::endl;
            m_deadTimer = nullptr;
        }
    }
}

void Character::render(sf::RenderWindow& drawingWindow) const
{
    drawingWindow.draw(m_characterRectangleShape);
}
