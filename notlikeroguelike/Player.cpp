#include "Player.h"
#include <SFML/Graphics.hpp>

PlayerClass::PlayerClass(sf::Vector2f position, int sideIAmOn) {
    
    setSide(sideIAmOn);
    setPosition(position);
    setSize({ 16.f,16.f });
    setOrigin(getSize().x/2,getSize().y/2 );
    setMovementDestination(getPosition());

    switch (sideIAmOn)
    {
    case 0:
        setFillColor(sf::Color::Magenta);
        break;
    case 1:
        setFillColor(sf::Color::Blue);
        break;
    case 2:
        setFillColor(sf::Color::Yellow);
        break;
    case 3:
        setFillColor(sf::Color::Green);
        break;
    case 4:
        setFillColor(sf::Color::Cyan);
        break;
    default:
        break;
    }
}

const sf::Drawable* PlayerClass::getDrawable() const
{
    return this;
}

void PlayerClass::setMovementDestination(sf::Vector2f newDestination)
{
    m_movementDestination = newDestination;
}

sf::Vector2f PlayerClass::getMovementDestination()
{
    return m_movementDestination;
}

void PlayerClass::setSide(int newSide)
{
    m_sideIAmOn = newSide;
}

int PlayerClass::getSide()
{
    return m_sideIAmOn;
}

sf::FloatRect PlayerClass::getGlobalBounds() const
{
    return sf::RectangleShape::getGlobalBounds();
}

void PlayerClass::update(const float deltaTime, const sf::RenderWindow& window, sf::View& view, KeyboardAndMouseState& keyboardAndMouseState, std::vector<const Collidable*>& listOfCollidables, std::vector<Selectable*>& listOfSelectables)
{ 
    float moveX = 0.f, moveY = 0.f;
    moveX = (getMovementDestination().x - getPosition().x) / 2;
    moveY = (getMovementDestination().y - getPosition().y) / 2;
    move(moveX * deltaTime, moveY * deltaTime);

    if (keyboardAndMouseState.mouseRightReleased && keyboardAndMouseState.currentMousePosition == keyboardAndMouseState.mousePositionInWindowWhenRightOrMiddleMouseButtonWasLastPressed && getSelected())
    {
        setMovementDestination(keyboardAndMouseState.mousePositionInWorldWhenRightMouseButtonWasLastPressed);
    }
}
