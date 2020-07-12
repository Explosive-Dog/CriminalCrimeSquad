#include "Player.h"
#include <SFML/Graphics.hpp>

PlayerClass::PlayerClass(sf::Vector2f position, int sideIAmOn) {
    
    setSide(sideIAmOn);
    setPosition(position);
    setSize({ 16.f,16.f });
    setOrigin(getSize().x/2,getSize().y/2 );
    setMovementDestination(getPosition());
    setSideIAmOnColour(sideIAmOn);
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

sf::FloatRect PlayerClass::getCollidable()const 
{
    return getGlobalBounds();
}

void PlayerClass::setSideIAmOnColour(int side)
{
    switch (side)
    {
    case 0:
        setFillColor(sf::Color::Green);
        break;
    case 1:
        setFillColor(sf::Color::Blue);
        break;
    case 2:
        setFillColor(sf::Color::Red);
        break;
    case 3:
        setFillColor(sf::Color::Magenta);
        break;
    case 4:
        setFillColor(sf::Color::Cyan);
        break;
    case 5:
        setFillColor(sf::Color::Yellow);
        break;
    default:
        break;
    }
}

void PlayerClass::onCollide(const Collidable*)
{
    setFillColor(sf::Color::White);
}

void PlayerClass::checkCollidables(std::vector<const Collidable*> listOfCollidables)
{
    m_colliding = false;
    for (size_t index = 0; index != listOfCollidables.size(); ++index)
    {
        if (listOfCollidables[index] == this)
        {
            continue;
        }
        if (getCollidable().intersects(listOfCollidables[index]->getCollidable()))
        {
            m_colliding = true;
            onCollide(listOfCollidables[index]);
        }
    }
    if (m_colliding == false)
    {
        setSideIAmOnColour(getSide());
    }
}

void PlayerClass::update(const float deltaTime, const sf::RenderWindow& window, sf::View& view, KeyboardAndMouseState& keyboardAndMouseState, std::vector<const Collidable*>& listOfCollidables, std::vector<Selectable*>& listOfSelectables)
{ 
    checkCollidables(listOfCollidables);

    float moveX = 0.f, moveY = 0.f;
    moveX = (getMovementDestination().x - getPosition().x) / 2;
    moveY = (getMovementDestination().y - getPosition().y) / 2;
    move(moveX * deltaTime, moveY * deltaTime);

    if (keyboardAndMouseState.mouseRightReleased && keyboardAndMouseState.currentMousePosition == keyboardAndMouseState.mousePositionInWindowWhenRightOrMiddleMouseButtonWasLastPressed && getSelected())
    {
        setMovementDestination(keyboardAndMouseState.mousePositionInWorldWhenRightMouseButtonWasLastPressed);
    }
}
